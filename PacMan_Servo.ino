#include<Servo.h>
Servo S1;


void setup() {
    S1.attach(9);
    Serial.begin(9600);
    S1.write(180);
    delay(1000);
    S1.write(90);
    delay(1000);
    S1.write(0);
    
    delay(2000);
}

void loop() {
  while(Serial.available())
  {
    S1.write(Serial.read());
  }
}
