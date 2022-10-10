#include <Arduino.h>
bool serial_inincialized = false;

bool defineSerial()
{
    if (!serial_inincialized)
    {
        Serial.begin(115200);
        serial_inincialized = true;
    }
}

void printFromSerial(String postData)
{
    defineSerial();
    Serial.println(F("id_device_in\t bateria\t temperatura\t humedad\t flat\t flon\t timestamp\t numero_satelites\t varianza\t x\t y\t z\t total"));
    Serial.println(postData);
}