
void sdInitialization()
{

  Serial.print("Initializing SD card...");
  if (!SD.begin(SS))
  {
    Serial.println("initialization failed!");
    ESP.restart();
  }
  Serial.println("initialization done.");
}