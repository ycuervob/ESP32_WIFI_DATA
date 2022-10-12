#include <SPI.h>
#include <SD.h>

// Micro sd storage
File myFile;

bool sdInitialization() {
  if (!SD.begin(SS)) {
    return false;
  }
  return true;
}

void saveData(String postData, int httpResponseCode) {
  myFile = SD.open("/data.json", FILE_APPEND);

  if (myFile) {
    myFile.println(postData);
    myFile.close();
  } else {

  }
}