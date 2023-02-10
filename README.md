# ESP32_WIFI_DATA 👨🏻‍💻

Este dispositivo está basado en un microcontrolador y se utiliza para enviar datos a un servidor remoto. En esta documentación se describen las librerías utilizadas y la lógica general detrás del dispositivo.

## Librerías utilizadas 🗒

* [HartwareSerial](https://github.com/G6EJD/ESP32-Using-Hardware-Serial-Ports): Permite la manipulación de los puertos seriales (RX y TX) del ESP32, es un equivalente a la librería se SoftwareSerial para el arduino. Algunos dispositivos, como el GPS, requieren esta librería para funcionar.
* [TinyGps](https://github.com/mikalhart/TinyGPS): Permite la manipulación de los datos crudos arrojados por el GPS a través de los puertos seriales.
* [WIFI](https://github.com/espressif/arduino-esp32/tree/master/libraries/WiFi): Permite la conexión del ESP32 a una red wifi específica. Se requiere especificar el SSID y la contraseña de la red.
* [HTTPClient](https://github.com/espressif/arduino-esp32/tree/master/libraries/HTTPClient) : Permite la creación y envío de peticiones HTTP una vez se ha establecido una conexión a través de WiFi.h. También permite obtener el código de respuesta HTTP del servidor.
* [DTH22](https://github.com/adafruit/DHT-sensor-library): Permite el uso del sensor DHT.
* SPI.h: Habilita el uso de la interfaz SPI del ESP32 para conexión con el módulo Micro SD.
* [SD](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD): Permite el uso del módulo Micro SD para arduino. Contiene funciones para crear, eliminar y editar archivos.

## Lógica general del dispositivo 🦜

El dispositivo no mantendrá todos los módulos encendidos en todo momento, ya que esto sería un problema a nivel energético. En su lugar, los componentes como el GPS, el WiFi y el sensor de temperatura se encenderán y apagarán cada cierto tiempo, y los tiempos de encendido y apagado determinarán la toma de datos.

Los ciclos del dispositivo son variables y generalmente constan de 3 tiempos:

1. Almacenamiento de datos: El objetivo de este tiempo es tomar los datos arrojados por los diferentes componentes y guardarlos en la memoria Micro SD.
2. Envío de información: El objetivo de este tiempo es tomar los datos almacenados en la memoria Micro SD y enviarlos al servidor remoto. Este tiempo es una fracción del tiempo de reposo calculado.
3. Tiempo de reposo: El dispositivo estará en reposo durante este tiempo. Se calcula con respecto a la última velocidad registrada del dispositivo, y se puede calcular el tiempo de envío como una fracción del tiempo de reposo.

## main

* Unificado: Este folder incluye todo el código del proyecto
* Pruebas Individuales: Este folder incluye código para probar elementos separados en un ESP32
* Circuito/Placa 1: Este folder tiene los archivos para el programa kiCad con el circuito de una PCB
