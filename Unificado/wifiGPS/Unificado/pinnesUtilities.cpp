void pinesyvariables()
{
  pinMode(pinSD, OUTPUT);
  pinMode(pinTem, OUTPUT);
  pinMode(pinGps, OUTPUT);
}

void EncenderDispositivos()
{
  digitalWrite(pinSD, HIGH);
  digitalWrite(pinTem, HIGH);
  digitalWrite(pinGps, HIGH);
}

void ApagarDispositivos()
{
  digitalWrite(pinSD, LOW);
  digitalWrite(pinTem, LOW);
  digitalWrite(pinGps, LOW);
}