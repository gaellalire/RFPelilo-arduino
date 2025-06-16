// #define RADIOLIB_EXCLUDE_LR11X0 1
#define TIMEOUT_MILLI 500

#include <ArduinoBLE.h>
#include <ReadBufferFixedSize.h>
#include <WriteBufferFixedSize.h>
#include "rfpelilo.h"
#include <RadioLib.h>
#include <FieldStringBytes.h>


// CC1101 has the following connections:
// CS pin:    10
// GDO0 pin:  2
// RST pin:   unused
// GDO2 pin:  3
CC1101 radio = new Module(10, 2, RADIOLIB_NC, 3);

::rfpelilo::Main request_;
::rfpelilo::Main response_;

EmbeddedProto::ReadBufferFixedSize<550> read_buffer_;
EmbeddedProto::WriteBufferFixedSize<550> write_buffer_;


// create service
BLEService duplexService("473da924-c93a-11e9-a32f-2a2ae2dbcce4");
// create button characteristic and allow remote device to get notifications
BLEByteCharacteristic buttonCharacteristic("473dab7c-c93a-11e9-a32f-2a2ae2dbcce4",
                                           BLERead | BLENotify);
// create LED characteristic and allow remote device to read and write
BLEByteCharacteristic ledCharacteristic("473dacc6-c93a-11e9-a32f-2a2ae2dbcce4",
                                        BLERead | BLEWrite);

int16_t transmitError;

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    ;  // wait until USB CDC port connects...
  }

  if (radio.begin() != RADIOLIB_ERR_NONE) {
    while (true) {
      delay(1000);
    }
  }

  if (radio.setPromiscuousMode() != RADIOLIB_ERR_NONE) {
    while (true) {
      delay(1000);
    }
  }

  while (Serial.available()) {
    // empty buffer
    Serial.println("emptying " + String(Serial.read()));
  }

  // begin initialization
  BLE.begin();

  // set the local name that the peripheral advertises
  BLE.setLocalName("duplexPeripheral");
  // set the UUID for the service the peripheral advertises:
  BLE.setAdvertisedService(duplexService);

  // add the characteristics to the service
  duplexService.addCharacteristic(ledCharacteristic);
  duplexService.addCharacteristic(buttonCharacteristic);

  // add the service
  BLE.addService(duplexService);

  ledCharacteristic.writeValue(0);
  buttonCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();
  // Serial.println("Peripheral is running");

  // Serial.print("rf");
}

void sendRF(rfpelilo::SendRFRequest sendRFRequest) {
  response_.set_command_id(request_.get_command_id());
  //  radio.setModulation(Modulation. sendRFRequest.get_modulation());  // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
  if (radio.fixedPacketLengthMode(0) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_PACKET_LENGTH_ERROR);
    return;
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
  if (radio.setBitRate(sendRFRequest.get_dataRate()) != RADIOLIB_ERR_NONE) {
    response_.set_command_status(rfpelilo::CommandStatus::RF_DATA_RATE_ERROR);
    return;
  }
  int repeat = 1;
  if (sendRFRequest.has_repeat()) {
    repeat = sendRFRequest.get_repeat();
  }

  rfpelilo::CommandStatus transmitStatus = rfpelilo::CommandStatus::RF_TRANSMIT_FAILED;
  for (int i = 0; i < repeat; i++) {
    transmitError = radio.transmit((uint8_t *)sendRFRequest.get_data().get_const(), sendRFRequest.get_data().get_length());
    if (RADIOLIB_ERR_NONE == transmitError) {
      transmitStatus = rfpelilo::CommandStatus::OK;
    }
  }
  response_.set_command_status(transmitStatus);
}


void loop() {
  int last;
  read_buffer_.clear();
  while (!Serial.available()) {
  }
  uint32_t originalMessageSize = 0;
  uint32_t messageSize = 0;
  // read 2 bytes
  int8_t byte1 = Serial.read();
  read_buffer_.push(byte1);
  last = millis();
  int8_t byte2 = 0;
  int8_t byte = 0, byten1 = 0, bytem1 = 0, bytem2 = 0, bytem3 = 0;
  uint8_t fbyte = 0;

  do {
    while (!Serial.available()) {
      if (millis() - last > TIMEOUT_MILLI) {
        // timeout : clear input
        while (Serial.available()) { Serial.read(); }
        goto input_error;
      }
      last = millis();
    }
    byte2 = Serial.read();
    read_buffer_.push(byte2);
    if (EmbeddedProto::Error::NO_ERRORS != ::EmbeddedProto::WireFormatter::DeserializeVarint(read_buffer_, messageSize)) {
      // error : clear input
      while (Serial.available()) { Serial.read(); }
      goto input_error;
    }
    // read_buffer_.pop(byte);
    originalMessageSize = messageSize;
    // read_buffer_.push(byte2);
    if (read_buffer_.peek(fbyte)) {
      // not empty : 1 byte size
      messageSize--;
      // we already read one byte from the message
    }
    int bytem1set = 0;
    while (messageSize > 0) {
      while (!Serial.available()) {
        if (millis() - last > TIMEOUT_MILLI) {
          // timeout : clear input
          while (Serial.available()) { Serial.read(); }
          goto input_error;
        }
        last = millis();
      }
      byten1 = byte;

      byte = Serial.read();

      if (bytem1set == 0) {
        bytem1 = byte;
        bytem1set++;
      } else if (bytem1set == 1) {
        bytem2 = byte;
        bytem1set++;

      } else if (bytem1set == 2) {
        bytem3 = byte;
        bytem1set++;
      }
      // Serial.println(byte);
      read_buffer_.push(byte);
      //  originalMessageSize = byte;

      messageSize--;
    }
    //    Serial.println("Finished " + String(messageSize));


    write_buffer_.clear();
    const auto result = request_.deserialize(read_buffer_);
    if (EmbeddedProto::Error::NO_ERRORS == result) {
      // Serial.println("NO_ERRORS deserialize");
      rfpelilo::SendRFRequest sendRFRequest = request_.get_send_rf_request();
      sendRF(sendRFRequest);

      EmbeddedProto::FieldString<200> textValue;
      String s = String(byte1) + " DES_OK " + String(byte2) + " or " + String(originalMessageSize) + " length " + sendRFRequest.get_data().get_length() + " RADIOLIB_CC1101_MAX_PACKET_LENGTH " + String(RADIOLIB_CC1101_MAX_PACKET_LENGTH) + " transmitError " + String(transmitError);
      textValue.set(s.c_str());
      rfpelilo::ErrorMessage errorMessage;
      errorMessage.set_text(textValue);
      response_.set_error_message(errorMessage);


      ::EmbeddedProto::WireFormatter::SerializeVarint(response_.serialized_size(), write_buffer_);
      const auto wresult = response_.serialize(write_buffer_);
      if (EmbeddedProto::Error::NO_ERRORS == wresult) {
        Serial.write(write_buffer_.get_data(), write_buffer_.get_size());
      } else {
        goto input_error;
      }
    } else {
      goto input_error;
    }
    return;
  } while (false);

input_error:
  write_buffer_.clear();
  response_.set_command_id(-1);
  response_.set_command_status(rfpelilo::CommandStatus::ERROR);
  EmbeddedProto::FieldString<200> textValue;
  String s = String("input_error b1 ") + String(byte1) + " b2 " + String(byte2) + " or " + String(originalMessageSize) + " messageSize " + String(messageSize) + " fbyte " + String((int8_t)fbyte) + " ms " + String(messageSize) + " bytem1 " + String(bytem1) + " bytem2 " + String(bytem2) + " bytem3 " + String(bytem3) + " ... byten1 " + String(byten1) + " byten " + String(byte);
  textValue.set(s.c_str());
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
