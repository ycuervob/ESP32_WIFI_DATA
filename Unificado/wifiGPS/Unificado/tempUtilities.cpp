String *tempyhumedad()
{
  float temperatura = dht.readTemperature();
  float humedad = dht.readHumidity();
  Serial.println("Humedad: ");
  Serial.println(humedad);
  Serial.println("Temperatura: ");
  Serial.println(temperatura);

  String strArray[2] = {String(temperatura, 6), String(humedad, 6)};
  return strArray;
}