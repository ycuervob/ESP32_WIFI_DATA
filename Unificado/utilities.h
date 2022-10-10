struct gpsDataType {
  String flat;
  String flon;
  char* timestamp;
  String numero_satelites;
  String varianza;
};

struct temyhumDataType {
  String temperatura;
  String humedad;
};

struct acelerometroDataType {
  String x;
  String y;
  String z;
  String total;
};

struct paqueteDataType {
  String id_device;
  String bateria;
  temyhumDataType temyhDatos;
  gpsDataType gpsDatos;
  acelerometroDataType acelerometroDatos;
};



void setup();
void defineSerial();
void printFromSerial(String);
void ProcesamientoDeInformacion();
void acelerometroInicializacion();
void gpsInicialization();
void tempInicialization();
void pinesyvariables();
void EncenderDispositivos();
void ApagarDispositivos();
bool saveDataSD(String);
bool sdInitialization();
bool wifiInicializacion();
bool acelerometroAlto ();
acelerometroDataType acelerometro();
gpsDataType gpsDatos();
temyhumDataType tempyhumedad();
bool guardaDatosGeneral(struct paqueteDataType &postData);
String createPostData(struct paqueteDataType &postData);
void httpmyRequest(String);

