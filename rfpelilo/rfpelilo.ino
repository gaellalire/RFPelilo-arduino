// #define RF69_RADIO 1
// #define CC1101_RADIO 1
// #define BLE_ACTIVATED 1
// #define RF69_HIGH_POWER 1
#if not defined(LED_BUILTIN)
#define LED_BUILTIN 32
#endif
#if not defined(BOARD_NAME)
#define BOARD_NAME "ESP32-D0WD-V3"
#endif

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
#define RF69_RADIO 1
#define DATA_PIN  PIN_RFM_DIO2
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

bool receiving = false;
uint32_t receivingCommandId;
volatile uint8_t maxMessageLength = 100;

volatile uint8_t bitCount = 0;
volatile uint8_t rxBuffer[256];
volatile uint16_t rxIndex = 0;
volatile uint8_t currentByte = 0;

#if defined(ESP8266) || defined(ESP32)
ICACHE_RAM_ATTR
#endif
void readBit(void) {
  // read the data bit
  uint8_t bit = digitalRead(DATA_PIN);
  currentByte = (currentByte << 1) | bit;
  bitCount++;

  if (bitCount == 8) {
    if(rxIndex < maxMessageLength) {
      rxBuffer[rxIndex++] = currentByte;
    }
    currentByte = 0;
    bitCount = 0;
  }
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

  ConfigFSK_t config;
  int16_t beginError = radio.begin();
  if (beginError != RADIOLIB_ERR_NONE && beginError != RADIOLIB_ERR_UNSUPPORTED) {
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
#if defined(RF69_RADIO)

#if defined(RF69_HIGH_POWER) || defined(ARDUINO_ADAFRUIT_FEATHER_RP2040_RFM)
  int16_t setOutputPowerError = radio.setOutputPower(0, true);
  if (setOutputPowerError != RADIOLIB_ERR_NONE) {
    String errorText = String("Cannot setOutputPower ") + String(setOutputPowerError);
    sendError(errorText);
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }
#endif
#endif

}

void clearReceiving() {
  if (!receiving) {
    return;
  }
  response_.clear();
  response_.set_command_id(receivingCommandId);
  response_.set_has_next(false);
  radio.standby();
  rxIndex = 0;
  bitCount = 0;
  currentByte = 0;
  sendResponse();
  receiving = false;
}

void verifyReceiving() {
  if (!receiving || rxIndex != maxMessageLength) {
    return;
  }
  response_.clear();
  response_.set_command_id(receivingCommandId);
  response_.set_has_next(true);
  response_.mutable_receive_rf_response().mutable_data().set((unsigned char *)rxBuffer, rxIndex);
  radio.standby();
  rxIndex = 0;
  bitCount = 0;
  currentByte = 0;
  radio.receiveDirect();
  sendResponse();
}

void receiveRF(rfpelilo::ReceiveRFRequest receiveRFRequest) {
  response_.set_command_id(request_.get_command_id());
  response_.set_has_next(true);

  bool modulationHasDeviation = false;
  switch(receiveRFRequest.get_modulation()) {
    case 0: // FSK
    // default do nothing
    radio.setOOK(false);
    modulationHasDeviation = true;
    break;
    case 1: // ASK
    radio.setOOK(true);
    break;
  }
  maxMessageLength = receiveRFRequest.get_maxMessageLength();

  if (radio.setFrequency(receiveRFRequest.get_frequency()) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_FREQUENCY_ERROR);
    return;
  }
  if (modulationHasDeviation && receiveRFRequest.has_deviation()) {
    if (radio.setFrequencyDeviation(receiveRFRequest.get_deviation()) != RADIOLIB_ERR_NONE) {
      response_.set_command_status(rfpelilo::CommandStatus::RF_FREQUENCY_DEVIATION_ERROR);
      return;
    }
  }
  float bitRate = receiveRFRequest.get_dataRate();
  if (radio.setBitRate(bitRate) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_DATA_RATE_ERROR);
    return;
  }
  radio.setRxBandwidth(receiveRFRequest.get_bandwidth());
  radio.setRSSIThreshold(receiveRFRequest.get_rssiThreshold());
  radio.setDirectAction(readBit);

  radio.receiveDirect();
  receivingCommandId = request_.get_command_id();
  receiving = true;
  response_.set_command_status(rfpelilo::CommandStatus::RF_DATA_RATE_ERROR);
}


void sendRF(rfpelilo::SendRFRequest sendRFRequest) {
  response_.set_command_id(request_.get_command_id());

  bool modulationHasDeviation = false;
  switch(sendRFRequest.get_modulation()) {
    case 0: // FSK
    // default do nothing
    radio.setOOK(false);
    modulationHasDeviation = true;
    break;
    case 1: // ASK
    radio.setOOK(true);
    break;
  }
  uint32_t messageLength = sendRFRequest.get_data().get_length();
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
  if (modulationHasDeviation && sendRFRequest.has_deviation()) {
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
  radio.setFifoEmptyAction(fifoAdd);

  int16_t transmitError = RADIOLIB_ERR_NONE;
  rfpelilo::CommandStatus transmitStatus = rfpelilo::CommandStatus::RF_TRANSMIT_FAILED;
  uint8_t *txBuffPtr = (uint8_t *)sendRFRequest.get_data().get_const();
  for (int i = 0; i < repeat; i++) {
    if (messageLength > MAX_PACKET_LENGTH) {
#if defined(RF69_RADIO)
      messageLength++; // FIXME remove this hack, last byte is ignored
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
    String s = "TransmitError " + String(transmitError);
    response_.mutable_error_message().mutable_text().set(s.c_str());
  }
}

void sendError(String errorText) {
  write_buffer_.clear();
  response_.set_command_id(-1);
  response_.set_command_status(rfpelilo::CommandStatus::ERROR);
  response_.mutable_error_message().mutable_text().set(errorText.c_str());

  ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
  const auto wresult = response_.serialize(write_buffer_);
  if (EmbeddedProto::Error::NO_ERRORS == wresult) {
    Serial.write(write_buffer_.get_data(), write_buffer_.get_size());
  } else {
    Serial.println("Cannot print error");
  }
}

// unsigned char mes[3] = { 170, 25, 132 };
unsigned char mes[] = {
    /* 0xCC repeated many times ... */
    0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,

    0x0F, 0xD0, 0x14, 0x04, 0x91,
    0x7F, 0xDE, 0xB6, 0x4D, 0x0B, 
    0x5B, 0xC0, 0x30, 0x0C, 0x03, 
    0x00, 0xDF, 0xF0, 0x0C, 0x03, 
    0x00, 0xC0, 0x30, 0x0C, 0x03, 
    0x00, 0xC3, 0xF0, 0x0C, 0x03, 
    0x50, 0xC7, 0x71, 0x07, 0xF0
};

unsigned char mes1[] = {
    /* 0xCC repeated many times ... */
    0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,

    0x0F, 0xD0, 0x14, 0x04, 0x91,
    0x7F, 0xC3, 0x32, 0x5D, 0x03,
    0x04, 0xC6, 0x71, 0x07, 0xF0
};

unsigned char mes2[] = {
    /* 0xCC repeated many times ... */
    0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
    0xCC, 0xCC, 0xCC, 0xCC, 0xCC,

    0x0F, 0xD0, 0x14, 0x04, 0x91,
    0x7F, 0xC3, 0x32, 0x5D, 0x03,
    0x04, 0xC6, 0x71, 0x07, 0xF0
};


void sendMain() {
    int m = 0;
    rfpelilo::SendRFRequest sendRFRequest;
    ::EmbeddedProto::FieldBytes<255> data;
    data.set(mes1, sizeof(mes1));
    // sendRFRequest.set_modulation(mod % 2);
    sendRFRequest.set_modulation(1);
    sendRFRequest.set_data(data);
    
//    sendRFRequest.set_frequency(868.684); // scoreboard
    sendRFRequest.set_frequency(868.89325); // console
    sendRFRequest.set_deviation(15.0);
    sendRFRequest.set_dataRate(10.0);
    sendRFRequest.set_repeat(1);
      while (1) {
      digitalWrite(LED_BUILTIN, HIGH);
      
      m = (m+1)%3;
      if (m == 0) {
    data.set(mes1, sizeof(mes1));
      } else if (m == 1) {
    data.set(mes2, sizeof(mes2));
      } else if (m == 2) {
    data.set(mes, sizeof(mes));
      }
          sendRFRequest.set_data(data);
          

      sendRF(sendRFRequest);
      digitalWrite(LED_BUILTIN, LOW);
      delay(1300);
      }

}

void receiveMain() {
      Serial.println("receiveMain");

    rfpelilo::ReceiveRFRequest receiveRFRequest;
    // sendRFRequest.set_modulation(mod % 2);
    receiveRFRequest.set_modulation(1);
    
    receiveRFRequest.set_frequency(868.684); // scoreboard
//    sendRFRequest.set_frequency(868.89325); // console
    receiveRFRequest.set_deviation(15.0);
    receiveRFRequest.set_dataRate(10.0);
    receiveRFRequest.set_bandwidth(100.0);
    receiveRFRequest.set_rssiThreshold(-85);
    receiveRFRequest.set_maxMessageLength(100);
      //while (1) {
      receiveRF(receiveRFRequest);
      // response_.get_receive_rf_response().get_data();
      /*
      const unsigned char * buf = response_.get_receive_rf_response().get_data().get_const();
      for (int i = 0; i < 100; i++) {
        for (int bit = 7; bit >= 0; bit--) {
          Serial.print(bitRead(buf[i], bit));
        }
      }
      Serial.println();

      }
      */

}

void sendResponse() {
  write_buffer_.clear();
  ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
  if (EmbeddedProto::Error::NO_ERRORS == response_.serialize(write_buffer_)) {
    Serial.write(write_buffer_.get_data(), write_buffer_.get_size());
  } else {
    sendError("Cannot serialize");
  }
}

bool firstCommand = false;

void loop() {
  if (firstCommand) {
   sendMain();
//   receiveMain();
   firstCommand = false;
  }

  int last;
  read_buffer_.clear();

  while (!Serial.available()) {
    verifyReceiving();
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

    request_.clear();
    if (EmbeddedProto::Error::NO_ERRORS == request_.deserialize(read_buffer_)) {
      clearReceiving(); // clear previous receiving call
      response_.clear();
      switch (request_.get_which_content()) {
        case rfpelilo::Main::FieldNumber::SEND_RF_REQUEST:
          {
            rfpelilo::SendRFRequest sendRFRequest = request_.get_send_rf_request();
            digitalWrite(LED_BUILTIN, HIGH);
            sendRF(sendRFRequest);
            digitalWrite(LED_BUILTIN, LOW);
          }
          break;

        case rfpelilo::Main::FieldNumber::RECEIVE_RF_REQUEST:
          {
            rfpelilo::ReceiveRFRequest receiveRFRequest = request_.get_receive_rf_request();
            receiveRF(receiveRFRequest);
          }
          break;
        case rfpelilo::Main::FieldNumber::EMPTY:
          response_.set_command_id(request_.get_command_id());
          response_.set_command_status(rfpelilo::CommandStatus::OK);
          break;
      }

      sendResponse();
    } else {
      goto input_error;
    }
    return;
  } while (false);

input_error:
  sendError("Cannot deserialize");
}
