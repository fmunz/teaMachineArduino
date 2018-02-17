#include <Servo.h>

// Teemaschine 

Servo servo;

int zeit = 0;
int wiederhole = 0;
int fertig = 0;


int startPos = 85;  // ausgangsposition oben
int teePos =  35;   // pos im tee, bruehen
int teeAuf = 40;    // tee auf, schuetteln
int teeAb = 30;     // tee ab, schuetteln
int zeitAb = 80;    // geschwindigkeit sinken
int zeitAuf = 120;   // geschwindigkeit heben


// wie oft soll teebeutel geschuettelt werden
int anzSchuetteln = 3;
// anzahl auf und ab je schuetteln
int aufab = 3;

// schleifenvariablen
int a=0;
int r=0; 
int i=0;


// setup Hardware
void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  
}


void loop() {
    
  digitalWrite(10, HIGH);
  digitalWrite(6, LOW);
  delay(1000);
  
  // poti auslesen fuer gesamtzeit
  zeit = map(analogRead(4), 0, 1023, 0, 30000);
  zeit = zeit*5;

  servo.attach(11);         // servo hängt an pin 11
  servo.write(startPos);    // Ausgangsposition

  // langsames absenken von startPos auf teePos
  for (i= startPos; i > teePos; i--){
    servo.write(i);
    delay(zeitAb);
  }
  
  delay(zeit); 
  // schleife schuetteln
  for (r = 1; r <= anzSchuetteln; ++r) {
    // auf und ab  
    for (a = 1; a <= (aufab); ++a) {
      servo.write(teeAuf);
      delay(300);
      servo.write(teeAb);
      delay(300);
    }
    // warten, tee brueht jetzt wieder
    delay(zeit); 
  }

  // langsam nach oben, zb von teePos auf startPos
  for (a = teePos; a <= (startPos); a++) {
    servo.write(a);
    delay(zeitAuf);
  }
  
  // letzte Position, wieder in Ausgangsposition
  servo.write(startPos);
  delay(1000);
  servo.detach();
  
  // summer 
  digitalWrite(6, HIGH);
  delay(2000);
  digitalWrite(6, LOW);
  delay(3000);
  
  //LED blinken zum schluss 
  for (a = 1; a <= (500); ++a) {
    digitalWrite(10, LOW);
    delay(2000);
    digitalWrite(10, HIGH);
    delay(300);
  }

  
}
