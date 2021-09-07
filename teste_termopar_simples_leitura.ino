#include "max6675.h"

int SO = 4;
int CS = 5;
int CLK = 6;

MAX6675 sensor(CLK, CS, SO);

void setup()
{
  Serial.begin(9600);
  delay(1000);
}
void loop() 
{  
   Serial.println("Graus C = "); 
   Serial.println(sensor.readCelsius());
   delay(500);
}
