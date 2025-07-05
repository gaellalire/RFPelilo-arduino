// #define RF69_RADIO 1
// #define CC1101_RADIO 1
// #define BLE_ACTIVATED 1
// #define RF69_HIGH_POWER 1

#define TIMEOUT_MILLI 500
#define BLE_CHARACTERISTIC_SIZE 230

#if defined(BLE_ACTIVATED)
#include <ArduinoBLE.h>
#endif
#include <ReadBufferFixedSize.h>
#include <WriteBufferFixedSize.h>
#include "rfpelilo.h"
#include <RadioLib.h>
#include <FieldStringBytes.h>


#if defined(CC1101_RADIO)
// CC1101 has the following connections:
// CS pin:    10
// GDO0 pin:  2
// RST pin:   unused
// GDO2 pin:  3
CC1101 radio = new Module(10, 2, RADIOLIB_NC, 3);
#define MAX_PACKET_LENGTH RADIOLIB_CC1101_MAX_PACKET_LENGTH
#elif defined(RF69_RADIO)
// RF69 has the following connections:
// CS pin:    10
// DIO0 pin:  3
// RESET pin: 2
// DIO1 pin:  4
RF69 radio = new Module(10, 3, 2, 4);
#define MAX_PACKET_LENGTH RADIOLIB_RF69_MAX_PACKET_LENGTH
#elif defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)
// use internal radio pin
RF69 radio = new Module(16, 21, 17, 22);
#define MAX_PACKET_LENGTH RADIOLIB_RF69_MAX_PACKET_LENGTH
#endif

::rfpelilo::Main request_;
::rfpelilo::Main response_;

EmbeddedProto::ReadBufferFixedSize<550> read_buffer_;
EmbeddedProto::WriteBufferFixedSize<550> write_buffer_;

volatile bool fifoEmpty = false;

#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif
void fifoAdd(void) {
  // we can send more bytes
  fifoEmpty = true;
}

#if defined(BLE_ACTIVATED)

// create service
BLEService rfpeliloService("5b79ded9-8881-4628-b5cd-dd9ac8b69c53");
// 5b79ded9-8881-4628-b5cd-dd9ac8b69c53
// create TX characteristic and allow remote device to get notifications
BLECharacteristic txCharacteristic("5b79ded0-8881-4628-b5cd-dd9ac8b69c53",
                                   BLEWrite, BLE_CHARACTERISTIC_SIZE);
// create RX characteristic and allow remote device to read and write
BLECharacteristic rxCharacteristic("5b79ded1-8881-4628-b5cd-dd9ac8b69c53",
                                   BLERead | BLEIndicate, BLE_CHARACTERISTIC_SIZE);


void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
}

void txCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  int valueLength = characteristic.valueLength();
  characteristic.readValue(read_buffer_.get_data(), valueLength);
  read_buffer_.set_bytes_written(valueLength);
  byte b = 0;
  // first byte is size
  read_buffer_.pop(b);
  if (b & 0x80) {
    read_buffer_.pop(b);  // first byte is also size, no third because MTU < 230 < 255
  }

  write_buffer_.clear();
  if (EmbeddedProto::Error::NO_ERRORS == request_.deserialize(read_buffer_)) {
    if (request_.has_send_rf_request()) {
      rfpelilo::SendRFRequest sendRFRequest = request_.get_send_rf_request();
      // Serial.println(String("sendRFRequest freq ") + String(sendRFRequest.get_frequency()));
      digitalWrite(LED_BUILTIN, HIGH);
      sendRF(sendRFRequest);
      digitalWrite(LED_BUILTIN, LOW);

      ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
      if (EmbeddedProto::Error::NO_ERRORS == response_.serialize(write_buffer_)) {
        rxCharacteristic.writeValue(write_buffer_.get_data(), write_buffer_.get_size());
      }
    }
  }

  read_buffer_.clear();
}


#endif


void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  int16_t beginError = radio.begin();
  if (beginError != RADIOLIB_ERR_NONE) {
    String errorText = String("Cannot begin ") + String(beginError);
    sendError(errorText);
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }

  int16_t setPromiscuousModeError = radio.setPromiscuousMode();
  if (setPromiscuousModeError != RADIOLIB_ERR_NONE) {
    String errorText = String("Cannot setPromiscuousMode ") + String(setPromiscuousModeError);
    sendError(errorText);
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }

#if defined(RF69_RADIO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)
  radio.setFifoEmptyAction(fifoAdd);
#if defined(RF69_HIGH_POWER) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)
  radio.setOutputPower(0, true);
#endif
#endif

#if defined(BLE_ACTIVATED)

  // begin initialization

  BLE.begin();

  // set the local name that the peripheral advertises
  BLE.setLocalName(BOARD_NAME);
  // set the UUID for the service the peripheral advertises:
  BLE.setAdvertisedService(rfpeliloService);

  // add the characteristics to the service
  rfpeliloService.addCharacteristic(rxCharacteristic);
  rfpeliloService.addCharacteristic(txCharacteristic);

  // add the service
  BLE.addService(rfpeliloService);

  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  txCharacteristic.setEventHandler(BLEWritten, txCharacteristicWritten);


  // start advertising
  BLE.advertise();
#endif
}

void sendRF(rfpelilo::SendRFRequest sendRFRequest) {
  response_.set_command_id(request_.get_command_id());
  uint32_t messageLength = sendRFRequest.get_data().get_length();
  //  radio.setModulation(Modulation. sendRFRequest.get_modulation());  // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
  if (messageLength > MAX_PACKET_LENGTH) {
    if (radio.fixedPacketLengthMode(0) != RADIOLIB_ERR_NONE) {
      response_.set_command_status(rfpelilo::CommandStatus::RF_PACKET_LENGTH_ERROR);
      return;
    }
  } else {
    if (radio.fixedPacketLengthMode(messageLength) != RADIOLIB_ERR_NONE) {
      response_.set_command_status(rfpelilo::CommandStatus::RF_PACKET_LENGTH_ERROR);
      return;
    }
  }

  if (radio.setFrequency(sendRFRequest.get_frequency()) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_FREQUENCY_ERROR);
    return;
  }
  if (sendRFRequest.has_deviation()) {
    if (radio.setFrequencyDeviation(sendRFRequest.get_deviation()) != RADIOLIB_ERR_NONE) {
      response_.set_command_status(rfpelilo::CommandStatus::RF_FREQUENCY_DEVIATION_ERROR);
      return;
    }
  }
  float bitRate = sendRFRequest.get_dataRate();
  if (radio.setBitRate(bitRate) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_DATA_RATE_ERROR);
    return;
  }
  int repeat = 1;
  if (sendRFRequest.has_repeat()) {
    repeat = sendRFRequest.get_repeat();
  }

  int16_t transmitError = RADIOLIB_ERR_NONE;
  rfpelilo::CommandStatus transmitStatus = rfpelilo::CommandStatus::RF_TRANSMIT_FAILED;
  uint8_t *txBuffPtr = (uint8_t *)sendRFRequest.get_data().get_const();
  for (int i = 0; i < repeat; i++) {
    if (messageLength > MAX_PACKET_LENGTH) {
#if defined(RF69_RADIO) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)
      int remLength = messageLength;
      // calculate timeout (5ms + 500 % of expected time-on-air)
      RadioLibTime_t timeout = 5 + (RadioLibTime_t)((((float)(messageLength * 8)) / bitRate) * 5);
      RadioLibTime_t start = millis();

      transmitError = radio.startTransmit(txBuffPtr, messageLength);

      bool transmittedFlag = false;
      bool timeoutExpired = false;
      while (!transmittedFlag) {
        if (millis() - start > timeout) {
          // timeout
          timeoutExpired = true;
          break;
        }
        if (fifoEmpty) {
          // reset flag
          fifoEmpty = false;

          // add more bytes to the transmit buffer
          transmittedFlag = radio.fifoAdd(txBuffPtr, messageLength, &remLength);
        }
      }
      radio.standby();
      if (!timeoutExpired) {
        transmitStatus = rfpelilo::CommandStatus::OK;
      }
#endif
    } else {
      transmitError = radio.transmit((uint8_t *)sendRFRequest.get_data().get_const(), messageLength);
      if (RADIOLIB_ERR_NONE == transmitError) {
        transmitStatus = rfpelilo::CommandStatus::OK;
      }
    }
  }

  response_.set_command_status(transmitStatus);

  if (transmitError != RADIOLIB_ERR_NONE) {
    EmbeddedProto::FieldString<200> textValue;
    String s = "TransmitError " + String(transmitError);
    textValue.set(s.c_str());
    rfpelilo::ErrorMessage errorMessage;
    errorMessage.set_text(textValue);
    response_.set_error_message(errorMessage);
  }
}

void sendError(String errorText) {
  write_buffer_.clear();
  response_.set_command_id(-1);
  response_.set_command_status(rfpelilo::CommandStatus::ERROR);
  EmbeddedProto::FieldString<200> textValue;
  textValue.set(errorText.c_str());
  rfpelilo::ErrorMessage errorMessage;
  errorMessage.set_text(textValue);
  response_.set_error_message(errorMessage);
  ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
  const auto wresult = response_.serialize(write_buffer_);
  if (EmbeddedProto::Error::NO_ERRORS == wresult) {
    Serial.write(write_buffer_.get_data(), write_buffer_.get_size());
  } else {
    Serial.println("Cannot print error");
  }
}

void loop() {
  int last;
  read_buffer_.clear();

  while (!Serial.available()) {
#if defined(BLE_ACTIVATED)
    BLE.poll();
#endif
  }
  uint32_t messageSize = 0;
  // read 2 bytes
  uint8_t byte = Serial.read();
  read_buffer_.push(byte);
  last = millis();

  do {
    while (!Serial.available()) {
      if (millis() - last > TIMEOUT_MILLI) {
        // timeout : clear input
        while (Serial.available()) { Serial.read(); }
        goto input_error;
      }
      last = millis();
    }
    byte = Serial.read();
    read_buffer_.push(byte);
    if (EmbeddedProto::Error::NO_ERRORS != ::EmbeddedProto::WireFormatter::DeserializeVarint(read_buffer_, messageSize)) {
      // error : clear input
      while (Serial.available()) { Serial.read(); }
      goto input_error;
    }
    if (read_buffer_.peek(byte)) {
      // not empty : 1 byte size
      messageSize--;
      // we already read one byte from the message
    }
    while (messageSize > 0) {
      while (!Serial.available()) {
        if (millis() - last > TIMEOUT_MILLI) {
          // timeout : clear input
          while (Serial.available()) { Serial.read(); }
          goto input_error;
        }
        last = millis();
      }

      byte = Serial.read();

      read_buffer_.push(byte);

      messageSize--;
    }

    write_buffer_.clear();
    if (EmbeddedProto::Error::NO_ERRORS == request_.deserialize(read_buffer_)) {
      rfpelilo::SendRFRequest sendRFRequest = request_.get_send_rf_request();
      digitalWrite(LED_BUILTIN, HIGH);
      sendRF(sendRFRequest);
      digitalWrite(LED_BUILTIN, LOW);

      ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
      if (EmbeddedProto::Error::NO_ERRORS == response_.serialize(write_buffer_)) {
        Serial.write(write_buffer_.get_data(), write_buffer_.get_size());
      } else {
        sendError("Cannot serialize");
      }
    } else {
      goto input_error;
    }
    return;
  } while (false);

input_error:
  sendError("Cannot deserialize");
}
