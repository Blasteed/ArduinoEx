#define BUT 2
#define LED 3

int    iBut = 0;
int iButOld = 0;

void setup()
{
  pinMode(BUT,  INPUT);
  pinMode(LED, OUTPUT);
}

void loop()
{
  int sBut = digitalRead(BUT);

  if (sBut != iButOld && sBut) iBut = !iBut;

  iButOld = sBut;

  digitalWrite(LED, iBut);
}
