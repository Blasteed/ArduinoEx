//Alessandro Carfagna - IIS Marconi Tortona - 4^AE - 2020/2021 - Progetto: Cancello Automatico con Arduino Nano

#define BUT      4
#define LED      5
#define MOT_A    6
#define MOT_B    7
#define LAS_A    8
#define LAS_B    9
#define MOT_EN  10
#define ACT_A   11
#define ACT_B   12
#define PHOT_A  A6
#define PHOT_B  A7

#define PHOTO_RANGE 700

#define ON       1
#define OFF      0

#define SPEED   25
#define SHUT     0

int mGate;

#define HALT              0
#define START             1
#define TIME_LAS_START    2
#define TIME_BUT_START    3
#define TIME_LAS_BACK     4
#define TIME_BUT_BACK     5
#define BACK              6

#define LED_BLINK    350
#define SER_BLINK    300

#define MOT_DELAY  10000

unsigned long                  tTimer;

unsigned long        tTimerControlLed;
unsigned long      tTimerControlMotor;
unsigned long     tTimerControlSerial;



void setup()
{

  mGate = HALT;

  pinMode(BUT,     INPUT);
  pinMode(LED,    OUTPUT);
  pinMode(PHOT_A,  INPUT);
  pinMode(PHOT_B,  INPUT);
  pinMode(LAS_A,  OUTPUT);
  pinMode(LAS_B,  OUTPUT);
  pinMode(ACT_A,   INPUT);
  pinMode(ACT_B,   INPUT);
  pinMode(MOT_A,  OUTPUT);
  pinMode(MOT_B,  OUTPUT);
  pinMode(MOT_EN, OUTPUT);

  Serial.begin(9600);

}



void loop()
{

  tTimer = millis();

  int sButton      = digitalRead  (BUT);

  int sPhotoA      = analogRead(PHOT_A);
  int sPhotoB      = analogRead(PHOT_B);

  bool sActivatorA = digitalRead(ACT_A);
  bool sActivatorB = digitalRead(ACT_B);

  int iButtonOut;
  int iButtonOld;

  if (iButtonOld != sButton)
  {
    iButtonOut = !iButtonOut;
  }

  iButtonOld = sButton;

  switch (mGate)
  {

    case HALT:

      digitalWrite(LAS_A, OFF);
      digitalWrite(LAS_B, OFF);
      digitalWrite  (LED, OFF);

      if (sButton == ON)
      {
        mGate = START;
      }

      digitalWrite (MOT_A,   LOW);
      digitalWrite (MOT_B,   LOW);
      analogWrite  (MOT_EN, SHUT);

      break;



    case START:

      digitalWrite(LAS_A, ON);
      digitalWrite(LAS_B, ON);
      digitalWrite  (LED, ON);

      if (iButtonOut == ON)
      {
        mGate = TIME_BUT_START;
      }

      if (sPhotoA <= PHOTO_RANGE | sPhotoB <= PHOTO_RANGE)
      {
        mGate = TIME_LAS_START;
      }

      digitalWrite (MOT_A,   HIGH);
      digitalWrite (MOT_B,    LOW);
      analogWrite  (MOT_EN, SPEED);

      if (sActivatorB == ON)
      {
        digitalWrite (MOT_A,   LOW);
        digitalWrite (MOT_B,   LOW);
        analogWrite  (MOT_EN, SHUT);

        if (tTimerControlMotor != 0 & tTimer - tTimerControlMotor <= MOT_DELAY + 1000)
        {
          if (tTimer >= tTimerControlMotor + MOT_DELAY)
          {
            mGate = BACK;
          }
        }

        else
        {
          tTimerControlMotor = tTimer;
        }

      }

      break;



    case TIME_LAS_START:

      if (tTimer >= tTimerControlLed + LED_BLINK)
      {
        digitalWrite(LED, ON);
      }

      if (tTimer >= tTimerControlLed + LED_BLINK * 2)
      {
        digitalWrite(LED, OFF);
        tTimerControlLed = tTimer;
      }

      digitalWrite(LAS_A, ON);
      digitalWrite(LAS_B, ON);

      if (sPhotoA >= PHOTO_RANGE & sPhotoB >= PHOTO_RANGE)
      {
        mGate = START;
      }

      digitalWrite (MOT_A,   LOW);
      digitalWrite (MOT_B,   LOW);
      analogWrite  (MOT_EN, SHUT);

      break;



    case TIME_BUT_START:

      if (tTimer >= tTimerControlLed + LED_BLINK)
      {
        digitalWrite(LED, ON);
      }

      if (tTimer >= tTimerControlLed + LED_BLINK * 2)
      {
        digitalWrite(LED, OFF);
        tTimerControlLed = tTimer;
      }

      digitalWrite(LAS_A, OFF);
      digitalWrite(LAS_B, OFF);

      if (iButtonOut == OFF)
      {
        mGate = START;
      }

      digitalWrite (MOT_A,   LOW);
      digitalWrite (MOT_B,   LOW);
      analogWrite  (MOT_EN, SHUT);

      break;



    case TIME_LAS_BACK:

      if (tTimer >= tTimerControlLed + LED_BLINK)
      {
        digitalWrite(LED, ON);
      }

      if (tTimer >= tTimerControlLed + LED_BLINK * 2)
      {
        digitalWrite(LED, OFF);
        tTimerControlLed = tTimer;
      }

      digitalWrite(LAS_A, ON);
      digitalWrite(LAS_B, ON);

      digitalWrite      (MOT_A,  HIGH);
      digitalWrite      (MOT_B,   LOW);
      analogWrite      (MOT_EN, SPEED);

      if (sActivatorB == ON)
      {
        digitalWrite (MOT_A,   LOW);
        digitalWrite (MOT_B,   LOW);
        analogWrite  (MOT_EN, SHUT);

        if (tTimerControlMotor != 0 & tTimer - tTimerControlMotor <= MOT_DELAY + 1000)
        {
          if (tTimer >= tTimerControlMotor + MOT_DELAY)
          {
            mGate      =   BACK;
            iButtonOut =    OFF;
          }
        }

        else
        {
          tTimerControlMotor = tTimer;
        }
      }

      break;



    case TIME_BUT_BACK:

      if (tTimer >= tTimerControlLed + LED_BLINK)
      {
        digitalWrite(LED, ON);
      }

      if (tTimer >= tTimerControlLed + LED_BLINK * 2)
      {
        digitalWrite(LED, OFF);
        tTimerControlLed = tTimer;
      }

      digitalWrite(LAS_A, OFF);
      digitalWrite(LAS_B, OFF);

      if (iButtonOut == OFF)
      {
        mGate = BACK;
      }

      digitalWrite (MOT_A,   LOW);
      digitalWrite (MOT_B,   LOW);
      analogWrite  (MOT_EN, SHUT);

      break;



    case BACK:

      tTimerControlMotor = 0;

      digitalWrite(LAS_A, ON);
      digitalWrite(LAS_B, ON);
      digitalWrite  (LED, ON);

      if (iButtonOut == ON)
      {
        mGate = TIME_BUT_BACK;
      }

      if (sPhotoA <= PHOTO_RANGE | sPhotoB <= PHOTO_RANGE)
      {
        mGate = TIME_LAS_BACK;
      }

      digitalWrite (MOT_A,    LOW);
      digitalWrite (MOT_B,   HIGH);
      analogWrite  (MOT_EN, SPEED);

      if (sActivatorA == ON)
      {
        mGate = HALT;
      }

      break;

  }




  /*if (tTimer >= tTimerControlSerial + SER_BLINK)
    {

    Serial.write                                      (27);
    Serial.print                                    ("[H");

    Serial.println                                  ("  ");

    Serial.println     ("Alessandro Carfagna - IIS Marconi Tortona - 4^AE - 2020/2021 - Progetto: Cancello Automatico con Arduino Nano");

    Serial.println                                  ("  ");

    Serial.print            ("Button State:             ");
    Serial.println                               (sButton);
    Serial.print            ("Button Out State:         ");
    Serial.println                            (iButtonOut);

    Serial.println                                  ("  ");

    Serial.print            ("Machine State:            ");
    Serial.println                                 (mGate);

    Serial.println                                  ("  ");

    Serial.print                             ("Timer:   ");
    Serial.println                                (tTimer);
    Serial.print                       ("Motor Timer:   ");
    Serial.println                    (tTimerControlMotor);
    Serial.print                         ("Led Timer:   ");
    Serial.println                      (tTimerControlLed);
    Serial.print                      ("Serial Timer:   ");
    Serial.println                   (tTimerControlSerial);

    Serial.println                                  ("  ");

    Serial.print                       ("Photo A:       ");
    Serial.println                               (sPhotoA);
    Serial.print                       ("Photo B:       ");
    Serial.println                               (sPhotoB);

    Serial.println                                  ("  ");

    Serial.print           ("Activator A (Back):        ");
    Serial.println                           (sActivatorA);
    Serial.print           ("Activator B (Start):       ");
    Serial.println                           (sActivatorB);

    Serial.println                                  ("  ");

    Serial.print                  ("Laser A:            ");
    Serial.println                    (digitalRead(LAS_A));
    Serial.print                  ("Laser B:            ");
    Serial.println                    (digitalRead(LAS_B));

    Serial.println                                  ("  ");

    Serial.print                  ("Led:                ");
    Serial.println                      (digitalRead(LED));

    }

    if (tTimer >= tTimerControlSerial + SER_BLINK * 10)
    {

    Serial.write      (27);
    Serial.print   ("[2J");

    tTimerControlSerial = tTimer;

    }*/

}
