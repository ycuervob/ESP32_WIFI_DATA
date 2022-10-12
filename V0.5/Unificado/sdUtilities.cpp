#include <SPI.h>
#include <SD.h>

// Micro sd storage
File myFile;

bool sdInitialization() {

  Serial.print("Initializing SD card...");
  if (!SD.begin(SS)) {
    Serial.println("initialization failed!");
    return false;
  }
  Serial.println("initialization done.");
  return true;
}

void saveData(String postData, int httpResponseCode) {
  myFile = SD.open("/data.json", FILE_APPEND);
  Serial.print("Error sending data, storing in SD, http code: ");
  Serial.println(httpResponseCode);

  if (myFile) {
    Serial.print("Writing to data.json...");
    myFile.println(postData);
    myFile.close();
    Serial.println("done.");
  } else {
    Serial.println("error opening data.json");
  }
}