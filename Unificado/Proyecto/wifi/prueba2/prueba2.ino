#include <WiFi.h>
#include <HTTPClient.h>

// Sustituir por los datos de vuestro WiFi
const char* ssid = "UFI32";
const char* password = "1234567890";
String url = "http://192.168.100.41:3000";

void setup()
{
   Serial.begin(115200);
   delay(10);

   // Conectar WiFi
   WiFi.begin(ssid, password);
   while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
  /*Con la conexión ya realizada, se pasa a imprimir algunos datos importantes, como la dirección IP asignada a nuestro dispositivo*/
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
   HTTPClient http;
   WiFiClient client;

   if (http.begin(client, url)) //Iniciar conexión
   {
      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();  // Realizar petición

      if (httpCode > 0) {
         Serial.printf("[HTTP] GET... code: %d\n", httpCode);

         if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = http.getString();   // Obtener respuesta
            Serial.println(payload);   // Mostrar respuesta por serial
         }
      }
      else {
         Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
   }
   else {
      Serial.printf("[HTTP} Unable to connect\n");
   }

   delay(30000);
}
