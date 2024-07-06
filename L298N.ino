#include <Servo.h>
#include <SoftwareSerial.h>

Servo ST, SU, SV, SW, SX, SY, SZ;


#define PWM 3
#define A1 4
#define A2 5
#define B1 6
#define B2 7

#define TRIG A0
#define U1 15
#define U2 16
#define U3 17


int ss = 0;
unsigned long prvMillis = 0, crntMillis = 0;


void setup() {
  Serial.begin(9600);
  
  pinMode(PWM, OUTPUT);
  pinMode(A1, OUTPUT);    
  pinMode(A2, OUTPUT);
  pinMode(B1, OUTPUT);
  pinMode(B2, OUTPUT);
  
  pinMode(TRIG, OUTPUT);
  pinMode(U1, INPUT);
  pinMode(U2, INPUT);
  pinMode(U3, INPUT);

  analogWrite(PWM, 255);
  
  //ST.attach(3);
  //SU.attach(4);
  //SV.attach(5);
  //SW.attach(6);
  //SX.attach(7);
  SY.attach(8);
  SZ.attach(9);

 
  delay(2000);

}


void loop() {
  //Sensors();
  //delay(200);

  while(Serial.available())
  {
      switch(Serial.read())
        {

          case 'F':
          R_F();
          L_F();
          break;

          case 'R':
          R_B();
          L_F();
          break;

          case 'L':
          L_B();
          R_F();
          break;

          case 'B':
          R_B();
          L_B();
          break;

          case 'M':
          R_S();
          L_F();
          break;

          case 'N':
          L_S();
          R_F();
          break;

          case 'J':
          R_S();
          L_B();
          break;

          case 'K':
          L_S();
          R_B();
          break;

          case 'H':
          analogWrite(PWM, map(300, 0, 1023, 0, 255));
          L_F();
          R_F();
          break;

          case 'T':
          ST.write(Serial.parseInt());
          break;
          
          case 'U':
          SU.write(Serial.parseInt());
          break;

          case 'V':
          SV.write(Serial.parseInt());
          break;

          case 'W':
          SW.write(Serial.parseInt());
          break;

          case 'X':
          SX.write(Serial.parseInt());
          break;

          case 'Y':
          SY.write(Serial.parseInt());
          break;

          case 'Z':
          SZ.write(Serial.parseInt());
          break;

          case 'I':
          analogWrite(PWM, map(Serial.parseInt(), 0, 1023, 0, 255));
          break;
          
          case 'O':
          ss = 1;
          break;

          case 'P':
          ss = 0;
          break;

          case 'S':
          R_S();
          L_S();
          break;
          
          case 'Q':
          Bomb();
          break;
          
          default:
          break;
        } 
    }


    if(ss)
    {
      crntMillis = millis();
      if(crntMillis - prvMillis >= 250)
      {
         prvMillis = crntMillis;
         Sensors();
      }
    }
    
    
  }



/******************************/
/********* FUNCTIONS **********/
/******************************/




void R_F()
{
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
}

void R_B()
{
  digitalWrite(A1, 0);
  digitalWrite(A2, 1);
}

void R_S()
{
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
}


void L_F()
{
  digitalWrite(B1, 1);
  digitalWrite(B2, 0);
}

void L_B()
{
  digitalWrite(B1, 0);
  digitalWrite(B2, 1);
}

void L_S()
{
  digitalWrite(B1, 0);
  digitalWrite(B2, 0);
}

int Sensor1()
{
  digitalWrite(TRIG, 0);
  delay(5);
  digitalWrite(TRIG, 1);
  delay(10);
  digitalWrite(TRIG, 0);
  
  return((pulseIn(U1, 1))/57);
}

int Sensor2()
{
  digitalWrite(TRIG, 0);
  delay(5);
  digitalWrite(TRIG, 1);
  delay(10);
  digitalWrite(TRIG, 0);
  
  return((pulseIn(U2, 1))/57);
}

int Sensor3()
{
  digitalWrite(TRIG, 0);
  delay(5);
  digitalWrite(TRIG, 1);
  delay(10);
  digitalWrite(TRIG, 0);
  
  return((pulseIn(U3, 1))/57);
}

void Sensors()
{

    Serial.print(".....");
    Serial.print("|");
    Serial.print(Sensor1());
    Serial.print("|");
    Serial.print(Sensor2());
    Serial.print("|");
    Serial.print(Sensor3());
    Serial.print("|");
    Serial.println(".....");
}


void Bomb()
{
  analogWrite(PWM, map(280, 0, 1023, 0, 255));
  
  for(int j = 200; j >= 100; j-=50)
  {
    for(int i = 0; i <= 9; i++)
      {
        R_F();
        L_F();
        delay(j);
        R_S();
        L_S();
        delay(j);
      }
  }

  for(int i = 0; i <= 18; i++)
    {
        R_F();
        L_F();
        delay(50);
        R_S();
        L_S();
        delay(50);
    }
      
  R_F();
  L_F();
  delay(2200);
  R_S();
  L_S();

  analogWrite(PWM, map(1023, 0, 1023, 0, 255));

}
