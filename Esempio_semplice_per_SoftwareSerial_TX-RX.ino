// La libreria SoftwareSerial permette di creare delle Seriali Virtuali dove non sono più presenti quelle fisiche
#include <SoftwareSerial.h>

// Per utilizzare un transceiver su pin non normalmente adibiti a quello, si definiscono i pin
#define LED 3
#define RX 10
#define TX 11

// Definizione della seriale con i pin transceiver interessati
SoftwareSerial EmuSerial(RX, TX);

void setup()
{

  // Dichiarazione dell'input e dell'output del transceiver
  pinMode(RX,   INPUT);
  pinMode(TX,  OUTPUT);
  pinMode(LED, OUTPUT);

  // I delay sono utilizzati solo per sicurezza, per evitare che non si accavallino le attivazioni
  delay(300);

  // Inizializzazione della Seriale fisica per il funzionamento (Obbligatorio)
  Serial.begin(9600);

  // Inizializzazione Seriale Virtuale
  EmuSerial.begin(9600);

  delay(300);
}

void loop()
{

  char cReceipt, cEmuReceipt, cEmuReceiptFull;

  //  Condizione per la quale se sulla seriale è presente un dato allora svolge l'operazione
  if (Serial.available())
  {
    // La variabile che conterrà il carattere va a prenderlo dalla lettura dei dati in entrata
    cReceipt = Serial.read();

    // Stampa il contenuto della variabile, per linea, il nome del monitor seriale cambia in base al monitor seriale che vogliamo gestire, nel caso di un'altro Arduino metteremo il nome
    // della variabile virtuale che ci interessa per traferire le informazioni (Da noi all'altra scheda)
    EmuSerial.write(cReceipt);
  }

  // Questa condizione opera alla stessa maniera, ma al contrario, ovvero se sulla virtuale è presente un valore questo verrà trasmesso alla Seriale fisica inviandolo sull'RX dell'altra
  // scheda (Dall'altra scheda a noi)
  if (EmuSerial.available())
  {
    cEmuReceipt = EmuSerial.read();

    Serial.write(cEmuReceipt);
  }
  // Controllo per inserire ogni carattere ricevuto ad ogni giro di loop all'interno della variabile, in caso si utilizzino delle stringhe 
  if (cEmuReceipt != '\n')
  {
    cEmuReceiptFull = cEmuReceiptFull + cEmuReceipt;
  }

  // Condizioni per permettere l'accensione o lo spegnimento del LED, da notare che vengono utilizzate le virgolette singole, in quanto si sta lavorando su caratteri non costanti,
  // l'utilizzo di virgolette doppie comporterebbe il non funzionamento del codice. La terza condizion funziona da default, ovvero, se non doevessimo ricevere nessuno dei due
  // segnali sopra essa citati
  if      (cEmuReceiptFull == 'on')  digitalWrite(LED, HIGH);
  else if (cEmuReceiptFull == 'off') digitalWrite(LED,  LOW);
  else digitalWrite(LED, LOW);
}

// Ogni giro di loop viene processato un carattere alla volta dalla Seriale, non di più. La comunicazione avviene correttamente solo se le due Seriali si trovano alla stessa velocità.
