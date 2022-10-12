#include <SPI.h>
#include <SD.h>

// Micro sd storage
File myFile;

void sdInitialization() {
  if (!SD.begin(SS)) {
    ESP.restart();
  }
}

void saveData(String postData, int httpResponseCode) {
  myFile = SD.open("/data.json", FILE_APPEND);

  if (myFile) {
    myFile.println(postData);
    myFile.close();
  } else {
    ESP.restart();
  }
}