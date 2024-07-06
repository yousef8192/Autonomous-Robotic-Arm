#include <Servo.h>

Servo ST, SU, SV, SW, SX, SY, SZ;


//Replace all Prv variables and all the ServoEase functions with one variable and one function and pass the servo you want to move as a parameter to the function

#define TRIG 3 
#define ECHO 2  


int U1 = 81, V1 = 139, W1 = 41, X1 = 139, Y1 = 120, Z1 = 145;
int U2 = 167, V2 = 99, W2 = 40, X2 = 149, Y2 = 175, Z2 = 145;
int SSS = 0, tmp = 0, Stmp = 0, Object_Distance = 1;
unsigned long prvMillis = 0, crntMillis = 0;
int PrvU = 90, PrvV = 90, PrvW = 90, PrvX = 90, PrvY = 90, PrvZ = 90;



void setup() {
  Serial.begin(9600);
  
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  SZ.attach(A5);  //19  
  delay(1000);
  SZ.write(90);
  delay(1000);
  
  SY.attach(A4);  //18
  delay(1000);
  
  SX.attach(A3);  //17
  delay(1000);
  
  SW.attach(A2);  //16
  delay(1000);
  
  SV.attach(A1);  //15 
  delay(1000);
  
  SU.attach(A0);  //A0
  
  
  delay(2000);

  

}
 
  




void loop() 
{



  while(Serial.available())
  {
      switch(Serial.read())
        {
          case 'U':
          SU.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case 'V':
          SV.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case 'W':
          SW.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case 'X':
          SX.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case 'Y':
          SY.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case 'Z':
          SZ.write(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;




          //////////////////////////////////////////
          //Object_Position
          case 'u':   
          U1 = Serial.parseInt();
          break;

          case 'v':   
          V1 = Serial.parseInt();
          break;

          case 'w':   
          W1 = Serial.parseInt();
          break;

          case 'x':   
          X1 = Serial.parseInt();
          break;

          case 'y':   
          Y1 = Serial.parseInt();
          break;

          case 'z':   
          Z1 = Serial.parseInt();
          break;
          //////////////////////////////////////////////



          //////////////////////////////////////////
          //Box_Position
          case '*':   
          U2 = Serial.parseInt();
          break;

          case '(':   
          V2 = Serial.parseInt();
          break;

          case ')':   
          W2 = Serial.parseInt();
          break;

          case '-':   
          X2 = Serial.parseInt();
          break;

          case '+':   
          Y2 = Serial.parseInt();
          break;

          case '=':   
          Z2 = Serial.parseInt();
          break;
          //////////////////////////////////////////////


          case '!':   //U
          tmp = SSS;
          SSS = 0;
          PrvU = SU.read();
          ServoEaseU(map(Serial.parseInt(), 0, 2200, 0, 180));
          Serial.println("OK");
          SSS = tmp;
          break;

          case '@':   //V
          PrvV = SV.read();
          ServoEaseV(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case '#':   //W
          PrvW = SW.read();
          ServoEaseW(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case '$':   //X
          PrvX = SX.read();
          ServoEaseX(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case '%':   //Y
          PrvY = SY.read();
          ServoEaseY(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          case '&':   //Z
          PrvZ = SZ.read();
          ServoEaseZ(map(Serial.parseInt(), 0, 2200, 0, 180));
          break;

          
          case 'I':   //Sensor_On
          SSS = 1;
          break;

          case 'O':   //Sensor_Off
          SSS = 0;
          break;

          case 'A':   //Object_Distance
          Object_Distance = Serial.parseInt();
          break;
                    
          default:
          break;
        } 
   }

   if(SSS)
    {
      crntMillis = millis();
      if(crntMillis - prvMillis >= 1000)
      {
         prvMillis = crntMillis;
         
         //////////////1st_Sensor_Trigger/////////////////
         digitalWrite(TRIG, 0);
         delayMicroseconds(5);
         digitalWrite(TRIG, 1);
         delayMicroseconds(10);
         digitalWrite(TRIG, 0);
         Stmp = (pulseIn(ECHO, 1))/57;      //Save Sensor Reading
         Serial.println(Stmp);              //Send Sensor Reading to the App
         //////////////1st_Sensor_Trigger/////////////////
         
         if(Stmp <= Object_Distance)
         {
            delay(1000);
            //////////////2nd_Sensor_Trigger/////////////////
            digitalWrite(TRIG, 0);
            delayMicroseconds(5);
            digitalWrite(TRIG, 1);
            delayMicroseconds(10);
            digitalWrite(TRIG, 0);
            Stmp = (pulseIn(ECHO, 1))/57;      //Save Sensor Reading
            Serial.println(Stmp);              //Send Sensor Reading to the App
            //////////////2nd_Sensor_Trigger/////////////////
            
            if(Stmp <= Object_Distance)
            {
              delay(1000);
              //////////////3rd_Sensor_Trigger/////////////////
              digitalWrite(TRIG, 0);
              delayMicroseconds(5);
              digitalWrite(TRIG, 1);
              delayMicroseconds(10);
              digitalWrite(TRIG, 0);
              Stmp = (pulseIn(ECHO, 1))/57;      //Save Sensor Reading
              Serial.println(Stmp);              //Send Sensor Reading to the App
              //////////////3rd_Sensor_Trigger/////////////////

              if(Stmp <= Object_Distance)
              {
                delay(500);
                Catch_Object();
              }
              
            }
            
         }
      }
    }

 }



/******************************/
/********* FUNCTIONS **********/
/******************************/


  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseU(int x)
{ 
  if(x > PrvU)
  {
    for(int i=PrvU; i<=x; i++)
    {
      SU.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvU)
  {
    for(int i=PrvU; i>=x; i--)
    {
      SU.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvU = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseV(int x)
{
  if(x > PrvV)
  {
    for(int i=PrvV; i<=x; i++)
    {
      SV.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvV)
  {
    for(int i=PrvV; i>=x; i--)
    {
      SV.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvV = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseW(int x)
{
  if(x > PrvW)
  {
    for(int i=PrvW; i<=x; i++)
    {
      SW.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvW)
  {
    for(int i=PrvW; i>=x; i--)
    {
      SW.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvW = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseX(int x)
{
  if(x > PrvX)
  {
    for(int i=PrvX; i<=x; i++)
    {
      SX.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvX)
  {
    for(int i=PrvX; i>=x; i--)
    {
      SX.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvX = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseY(int x)
{
  if(x > PrvY)
  {
    for(int i=PrvY; i<=x; i++)
    {
      SY.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvY)
  {
    for(int i=PrvY; i>=x; i--)
    {
      SY.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvY = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ServoEaseZ(int x)
{
  if(x > PrvZ)
  {
    for(int i=PrvZ; i<=x; i++)
    {
      SZ.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  if(x < PrvZ)
  {
    for(int i=PrvZ; i>=x; i--)
    {
      SZ.write(i); //turn servo by 1 degrees
      delay(10);        //delay for smoothness
    }
  }

  PrvY = x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Sensor()
{
  digitalWrite(TRIG, 0);
  delayMicroseconds(5);
  digitalWrite(TRIG, 1);
  delayMicroseconds(10);
  digitalWrite(TRIG, 0);
  Serial.println((pulseIn(ECHO, 1))/57);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Catch_Object()
{

  //Return to Default Position
  ServoEaseV(90);
  ServoEaseW(90);
  ServoEaseU(90);
  ServoEaseX(90);
  ServoEaseY(90);

  //Go to Object

  ServoEaseZ(145);   //145    //
  ServoEaseU(U1);   //86      //
  ServoEaseV(V1);   //133     //
  ServoEaseW(W1);   //25      //
  ServoEaseY(Y1);   //170     //
  ServoEaseX(X1);   //121     //



  delay(2000);
  
  //Catch Object
  ServoEaseZ(40);


  delay(500);

  
  //Return to Default Position
  ServoEaseV(90);
  ServoEaseW(90);
  ServoEaseU(90);
  ServoEaseX(90);
  ServoEaseY(90);


  //Go to Box
  ServoEaseY(Y2);   //
  ServoEaseX(X2);   //
  ServoEaseW(W2);   //
  ServoEaseV(V2);   //
  ServoEaseU(U2);   //

  delay(1000);

  //Throw the Object
  ServoEaseZ(140);

  delay(1000);
  
  //Return to Default Position
  ServoEaseV(90);
  ServoEaseW(90);
  ServoEaseU(90);
  ServoEaseX(90);
  ServoEaseY(90);

  
  
}
