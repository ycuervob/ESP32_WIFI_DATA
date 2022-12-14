/*
  SD card read/write
// comment
  This example shows how to read and write data to and from an SD card file
  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

*/

#include <SPI.h>
#include <SD.h>

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  Serial.print("Initializing SD card...");

  if (!SD.begin(SS)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("/data.json",FILE_APPEND);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to data.json...");
   
    for(int i = 0; i<100; i++){
      myFile.println(i);
    }
    // close the file:
     
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening data.json");
  }
}

void loop() {
  // nothing happens after setup
}
