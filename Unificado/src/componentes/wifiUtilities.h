#ifndef MYFILE_H
#define MYFILE_H

bool wifiInicializacion(const char * ssid, const char * password);

byte httpmyRequest(String postData, const char * serverName);

#endif // MYFILE_H