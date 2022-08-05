// Definizione pin utilzzati per bottone e LED
#define BUT 2
#define LED 3

// Definizione degli stati del pulsante. Il primo di ritenuta, il secondo per memorizzare lo stato passato dello stesso
int    iBut = 0;
int iButOld = 0;

void setup ()
{
  
  // Definizione modalità di funzione dei pin
  pinMode ( BUT,  INPUT );
  pinMode ( LED, OUTPUT );
}

void loop ()
{
  
  // Attivazione della lettura digitale del pin del pulsante
  int sBut = digitalRead ( BUT );

  // Se lo stato memorizzato e lo stato attuale, nel momento in cui il pulsante venisse premuto, sono diversi. La variabile
  // contenente lo stato del pulsante da utilizzare inverte il suo stato
  if ( sBut != iButOld && sBut ) iBut = !iBut;

  // La memorizzazione del pulsante si aggiorna all'attuale
  iButOld = sBut;

  // Il led assume lo stato di utilizzo del pulsante
  digitalWrite ( LED, iBut );
}
