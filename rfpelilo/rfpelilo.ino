#include <ELECHOUSE_CC1101_SRC_DRV.h>
#include <ReadBufferFixedSize.h>
#include "rfpelilo.h"

::rfpelilo::Main main_;

EmbeddedProto::ReadBufferFixedSize<256> read_buffer_;

byte transmitt_byte[11] = { 72, 101, 108, 108, 111, 32, 87, 111, 114, 108, 100 };
// {72,101,108,108,111,32,87,111,114,108,100};

// 48, 65. 6c, 6c, 6f, 20,57, 6f, 72, 6c, 64
// h.  e.  l   l.  o.  _  w   o.  r.  l.   d
// 0b 48 65 6c 6c 6f 20 57 6f 72 6c 64 0
char *transmitt_char = "Hello World";

void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ;  // wait until USB CDC port connects... Needed for Leonardo only
  }

  if (ELECHOUSE_cc1101.getCC1101()) {  // Check the CC1101 Spi connection.
    Serial.println("Connection OK");
  } else {
    Serial.println("Connection Error");
  }

  ELECHOUSE_cc1101.Init();               // must be set to initialize the cc1101!
  ELECHOUSE_cc1101.setCCMode(1);         // set config for internal transmission mode.
  ELECHOUSE_cc1101.setModulation(0);     // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
  ELECHOUSE_cc1101.setMHZ(433.92);       // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
  ELECHOUSE_cc1101.setDeviation(47.60);  // Set the Frequency deviation in kHz. Value from 1.58 to 380.85. Default is 47.60 kHz.
  ELECHOUSE_cc1101.setChannel(0);        // Set the Channelnumber from 0 to 255. Default is cahnnel 0.
  ELECHOUSE_cc1101.setChsp(199.95);      // The channel spacing is multiplied by the channel number CHAN and added to the base frequency in kHz. Value from 25.39 to 405.45. Default is 199.95 kHz.
  ELECHOUSE_cc1101.setRxBW(812.50);      // Set the Receive Bandwidth in kHz. Value from 58.03 to 812.50. Default is 812.50 kHz.
  ELECHOUSE_cc1101.setDRate(99.97);      // Set the Data Rate in kBaud. Value from 0.02 to 1621.83. Default is 99.97 kBaud!
  ELECHOUSE_cc1101.setPA(10);            // Set TxPower. The following settings are possible depending on the frequency band.  (-30  -20  -15  -10  -6    0    5    7    10   11   12) Default is max!
  ELECHOUSE_cc1101.setSyncMode(0);       // Combined sync-word qualifier mode. 0 = No preamble/sync. 1 = 16 sync word bits detected. 2 = 16/16 sync word bits detected. 3 = 30/32 sync word bits detected. 4 = No preamble/sync, carrier-sense above threshold. 5 = 15/16 + carrier-sense above threshold. 6 = 16/16 + carrier-sense above threshold. 7 = 30/32 + carrier-sense above threshold.
                                         //  ELECHOUSE_cc1101.setSyncWord(211, 145); // Set sync word. Must be the same for the transmitter and receiver. (Syncword high, Syncword low)
  ELECHOUSE_cc1101.setAdrChk(0);         // Controls address check configuration of received packages. 0 = No address check. 1 = Address check, no broadcast. 2 = Address check and 0 (0x00) broadcast. 3 = Address check and 0 (0x00) and 255 (0xFF) broadcast.
  ELECHOUSE_cc1101.setAddr(0);           // Address used for packet filtration. Optional broadcast addresses are 0 (0x00) and 255 (0xFF).
  ELECHOUSE_cc1101.setWhiteData(0);      // Turn data whitening on / off. 0 = Whitening off. 1 = Whitening on.
  ELECHOUSE_cc1101.setPktFormat(0);      // Format of RX and TX data. 0 = Normal mode, use FIFOs for RX and TX. 1 = Synchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins. 2 = Random TX mode; sends random data using PN9 generator. Used for test. Works as normal mode, setting 0 (00), in RX. 3 = Asynchronous serial mode, Data in on GDO0 and data out on either of the GDOx pins.
  ELECHOUSE_cc1101.setLengthConfig(2);   // 0 = Fixed packet length mode. 1 = Variable packet length mode. 2 = Infinite packet length mode. 3 = Reserved
  ELECHOUSE_cc1101.setPacketLength(0);   // Indicates the packet length when fixed packet length mode is enabled. If variable packet length mode is used, this value indicates the maximum packet length allowed.
  ELECHOUSE_cc1101.setCrc(0);            // 1 = CRC calculation in TX and CRC check in RX enabled. 0 = CRC disabled for TX and RX.
  ELECHOUSE_cc1101.setCRC_AF(0);         // Enable automatic flush of RX FIFO when CRC is not OK. This requires that only one packet is in the RXIFIFO and that packet length is limited to the RX FIFO size.
  ELECHOUSE_cc1101.setDcFilterOff(0);    // Disable digital DC blocking filter before demodulator. Only for data rates ≤ 250 kBaud The recommended IF frequency changes when the DC blocking is disabled. 1 = Disable (current optimized). 0 = Enable (better sensitivity).
  ELECHOUSE_cc1101.setManchester(0);     // Enables Manchester encoding/decoding. 0 = Disable. 1 = Enable.
  ELECHOUSE_cc1101.setFEC(0);            // Enable Forward Error Correction (FEC) with interleaving for packet payload (Only supported for fixed packet length mode. 0 = Disable. 1 = Enable.
                                         //  ELECHOUSE_cc1101.setPRE(0);             // Sets the minimum number of preamble bytes to be transmitted. Values: 0 : 2, 1 : 3, 2 : 4, 3 : 6, 4 : 8, 5 : 12, 6 : 16, 7 : 24
                                         // ELECHOUSE_cc1101.setPQT(0);             // Preamble quality estimator threshold. The preamble quality estimator increases an internal counter by one each time a bit is received that is different from the previous bit, and decreases the counter by 8 each time a bit is received that is the same as the last bit. A threshold of 4∙PQT for this counter is used to gate sync word detection. When PQT=0 a sync word is always accepted.
  ELECHOUSE_cc1101.setAppendStatus(0);   // When enabled, two status bytes will be appended to the payload of the packet. The status bytes contain RSSI and LQI values, as well as CRC OK.

  Serial.println("Tx Mode");
}

void loop() {
  read_buffer_.clear();
  while (!Serial.available()) {
  }
  while (!Serial.available()) {
    read_buffer_.push(Serial.read());
  }
  const auto result = main_.deserialize(read_buffer_);
  if (EmbeddedProto::Error::NO_ERRORS == result) {
    rfpelilo::SendRFRequest sendRFRequest = main_.get_send_rf_request();

    ELECHOUSE_cc1101.setModulation(sendRFRequest.get_modulation());  // set modulation mode. 0 = 2-FSK, 1 = GFSK, 2 = ASK/OOK, 3 = 4-FSK, 4 = MSK.
    ELECHOUSE_cc1101.setMHZ(sendRFRequest.get_frequency());          // Here you can set your basic frequency. The lib calculates the frequency automatically (default = 433.92).The cc1101 can: 300-348 MHZ, 387-464MHZ and 779-928MHZ. Read More info from datasheet.
    if (sendRFRequest.has_deviation()) {
      ELECHOUSE_cc1101.setDeviation(sendRFRequest.get_deviation());  // Set the Frequency deviation in kHz. Value from 1.58 to 380.85. Default is 47.60 kHz.
    }
    ELECHOUSE_cc1101.setDRate(sendRFRequest.get_dataRate());  // Set the Data Rate in kBaud. Value from 0.02 to 1621.83. Default is 99.97 kBaud!
    send(sendRFRequest.get_data().get_const(), sendRFRequest.get_data().get_length());
  }

  Serial.println("print4");

  //3 different methods to send data without gdo
  //When sending, we give a little time to completely transmit the message (time in millis).
  //You can shorten the time. It depends on the data rate and the packet length. Just try it out for fine tuning.

  //Transmitt "Hello World" from byte format.
  // ELECHOUSE_cc1101.SendData(transmitt_byte, 11, 100);


  // trxstate=1;

  send(transmitt_byte, 11);

  delay(2000);

  /*
    Serial.println("print2");

//Transmitt "Hello World" from char format.
ELECHOUSE_cc1101.SendData(transmitt_char, 100);
delay(2000);
    Serial.println("print3");


//Transmitt "Hello World" from char format directly.
ELECHOUSE_cc1101.SendData("Hello World", 100);
delay(2000);
*/
}

void send(const byte *data, byte size) {
  ELECHOUSE_cc1101.SpiWriteBurstReg(CC1101_TXFIFO, (byte *)data, size);  //write data to send
  ELECHOUSE_cc1101.SpiStrobe(CC1101_SIDLE);
  ELECHOUSE_cc1101.SpiStrobe(CC1101_STX);  //start send
  waitTXDone();
  ELECHOUSE_cc1101.SpiStrobe(CC1101_SFTX);  //flush TXfifo
}

void waitTXDone() {  //wait for end of transmission : FIFO size=0 cc1101.pdf p94
  int txbytes;
  do {
    txbytes = ELECHOUSE_cc1101.SpiReadStatus(CC1101_TXBYTES);
  } while (txbytes > 0);
}
