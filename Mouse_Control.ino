int VRx = A0;
int VRy = A1;
int SW = 2;
int flexPin = A2;
int flexPin1 = A3;

float VCC = 5;
float R_DIV = 10000.0;
float flatResistance = 25000.0;
float bendResistance = 100000.0;
int xPosition = 0;
int yPosition = 0;
int SW_state = 0;
int mapX = 0;
int mapY = 0;

void setup() {
  Serial.begin(9600);

  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(flexPin, INPUT);
  pinMode(flexPin1, INPUT);
  pinMode(SW, INPUT_PULLUP);

}

void loop() {
  if (Serial.available())
  {
    String s = (String)Serial.read();
    while (true)
    {
      int ADCflex = analogRead(flexPin);
      int ADCflex1 = analogRead(flexPin1);

      float Vflex = ADCflex * VCC / 1023.0;
      float Rflex = R_DIV * (VCC / Vflex - 1.0);
      float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);

      float Vflex1 = ADCflex1 * VCC / 1023.0;
      float Rflex1 = R_DIV * (VCC / Vflex1 - 1.0);
      float angle1 = map(Rflex1, flatResistance, bendResistance, 0, 90.0);

      xPosition = analogRead(VRx);
      yPosition = analogRead(VRy);
      SW_state = digitalRead(SW);
      mapX = map(xPosition, 0, 1023, 0, 1023);
      mapY = map(yPosition, 0, 1023, 0, 1023);
      Serial.print(",");
      String x = (String)mapX;
      String y = (String)mapY;


      Serial.print(format(x));
      Serial.print(" ");


      Serial.print(format(y));
      Serial.print(".");

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
      Serial.print("|");

      delay(200);
    }
  }
}

String format(String a)
{
  String temp = " ";
  if (a.length() < 5)
  {

    if (a.charAt(0) == '-')
    {
      String sign = a.substring(a.indexOf('-') + 1, a.length());
      temp = sign;
      for (int i = 0; i < 4 - sign.length(); i++)
      {
        temp = "0" + temp;
      }

      temp = "-" + temp;
    }


    else
    {
      temp = a;
      for (int i = 0; i < 5 - a.length(); i++)
      {
        temp = "0" + temp;
      }
    }
    return temp;
  }
}
