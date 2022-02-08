// Definizione dei PIN
#define TMP A0
#define BUT  2
#define OUT  3

// Definizione stati di ON e OFF per comodità
#define OFF 0
#define ON  1

const float fVal = 0.488; // Vcc (5V) / 1024

int    iBut = 1;
int iButOld = 0;

void setup()
{
  pinMode(TMP,  INPUT);
  pinMode(OUT, OUTPUT);
  pinMode(BUT,  INPUT);
}

void loop()
{

  // Autoritenuta Pulsante
  int sBut = digitalRead(BUT);

  if (sBut != iButOld && sBut) iBut = !iBut;
  
  iButOld = sBut;

  float sVin = analogRead(TMP);

  // Conversione Valore V in Gradi
  float fTemp = (fVal * sVin) - 50.0;

  // Controllo temperatura e attivazione pulsante, controllo uscita
  if (iBut)
  {
    if (fTemp > 19.0) digitalWrite(OUT,  ON);
    else              digitalWrite(OUT, OFF);
  }
  else digitalWrite(OUT, OFF);
}
