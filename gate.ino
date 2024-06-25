#include <Servo.h>
Servo servoMain; 
int trigpin = D5;
int echopin = D6;
int ledIjo = D7;
int buzzerPin = D0;
int distance;
float duration;
float cm;

#define NOTE_Eb 311 
#define NOTE_G  392
#define NOTE_Bb 466 

int durations[] = {200, 150, 300, 450, 150}; 

int numNotes = 5; 

void setup()
{
  Serial.begin(9600);
  servoMain.attach(D8); 
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledIjo, OUTPUT);
}

void loop()
{ 
  digitalWrite(trigpin, LOW);
  delay(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  cm = (duration*.0343)/2;
  distance = cm;

  Serial.print("Jarak: "); 
  Serial.println(distance);

  if(distance < 8)
  {
    servoMain.write(360);
    Serial.println("Servo bergerak 180 ");
    digitalWrite(ledIjo, HIGH);
    playMelody(); 
    delay(1500);
    digitalWrite(ledIjo, LOW); 
  }
   else{
     servoMain.write(180);
     Serial.println("Servo bergerak 0");
     delay(50);
   }

}

void playMelody() {
  for (int i = 0; i < numNotes; i++) {
    int note; 
    switch (i) { 
      case 0: 
      case 4:  note = NOTE_Eb; break;
      case 1: 
      case 3:  note = NOTE_G; break;
      case 2:  note = NOTE_Bb; break;
    }
    tone(buzzerPin, note, durations[i]);
    delay(durations[i] + 30); // Short pause between notes
  }
}
