#include<Wire.h>


int flexPin = A2;
int flexPin1 = A3;

float VCC = 5;
float R_DIV = 10000.0;
float flatResistance = 25000.0;
float bendResistance = 100000.0;

const int MPU_addr=0x68;

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;


int minVal=265;

int maxVal=402;


double x;

double y;

double z;


void setup(){

pinMode(flexPin,INPUT);
pinMode(flexPin1,INPUT);


Wire.begin();

Wire.beginTransmission(MPU_addr);

Wire.write(0x6B);

Wire.write(0);

Wire.endTransmission(true);

Serial.begin(9600);


}


void loop(){

pinMode(flexPin, INPUT);

pinMode(flexPin1, INPUT);

Wire.beginTransmission(MPU_addr);

Wire.write(0x3B);

Wire.endTransmission(false);

Wire.requestFrom(MPU_addr,14,true);

AcX=Wire.read()<<8|Wire.read();

AcY=Wire.read()<<8|Wire.read();

AcZ=Wire.read()<<8|Wire.read();


int ADCflex = analogRead(flexPin);
int ADCflex1 = analogRead(flexPin1);

float Vflex = ADCflex * VCC / 1023.0;
float Rflex = R_DIV * (VCC / Vflex - 1.0);
float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);

float Vflex1 = ADCflex1 * VCC / 1023.0;
float Rflex1 = R_DIV * (VCC / Vflex1 - 1.0);
float angle1 = map(Rflex1, flatResistance, bendResistance, 0, 90.0);



int xAng = map(AcX,minVal,maxVal,-90,90);

int yAng = map(AcY,minVal,maxVal,-90,90);

int zAng = map(AcZ,minVal,maxVal,-90,90);

 

x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);

y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);

z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);


//Serial.print("X:");
Serial.print(format(x));

Serial.print("|");

//Serial.print("Y:");
Serial.print(format(y));

Serial.print(",");

//Serial.print("Z:");
Serial.print(format(z));

Serial.print("$");

//Serial.print("\n");

 if (angle1 > 10 && angle < 10)
      {
        Serial.print("2");
      }

      else if (angle >= 10 && angle1 <= 10)
      {
        Serial.print("1");
      }
      else if (angle >= 10 && angle1 >= 10)
      {
        Serial.print("3");
      }
      else
      {
        Serial.print("0");
      }

      

delay(200);


}

String format(double d)
{
  String temp=(String)d;
  String str="";
  int counter=0;
  if(temp.length()<6)
  {
    counter=6-temp.length();

    while(counter!=0)
    {
      str='0'+str;
      counter--;
    }
  }

  return str+temp;
}
