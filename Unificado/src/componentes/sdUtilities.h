#ifndef SD_H
#define SD_H

bool sdInicializacion();
void endSD();
bool saveDataSD(String);
void getLine(String& , int* );
void getLine(String& , String* );
void setLine(int* );
byte readLine(String* , int* );

#endif // SD_H




