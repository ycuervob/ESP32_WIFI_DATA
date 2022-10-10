#include <Arduino.h>
bool serial_inincialized = false;
char* estados[4] = {"Datos erroneos, descartados","No wifi, guardado en SD", "No hay wifi ni SD --", "Enviado al servidor"};

bool defineSerial()
{
    if (!serial_inincialized)
    {
        Serial.begin(115200);
        serial_inincialized = true;
    }
}

void printFromSerial(String postData, byte status)
{
    defineSerial();
    Serial.println(F("id_device_in\t bateria\t temperatura\t humedad\t flat\t flon\t timestamp\t numero_satelites\t varianza\t x\t y\t z\t total"));
    Serial.println(postData);
    Serial.print("Estado del dato: ");
    Serial.println(estados[status]);
}