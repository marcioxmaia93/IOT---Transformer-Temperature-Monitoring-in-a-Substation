/*
This example shows how to connect MAX6675 to Cayenne using an Ethernet W5500 shield and send/receive sample data.

The CayenneMQTT Library is required to run this sketch. If you have not already done so you can install it from the Arduino IDE Library Manager.

Steps:
1. Download the Ethernet2 library (https://github.com/adafruit/Ethernet2) as a zip file.
2. From the Arduino IDE Include Library menu select Add .ZIP Library and add the downloaded Ethernet2 zip library.
3. Set the Cayenne authentication info to match the authentication info from the Dashboard.
4. Compile and upload the sketch.
5. A temporary widget will be automatically generated in the Cayenne Dashboard. To make the widget permanent click the plus sign on the widget.
*/

//#define CAYENNE_DEBUG       // Uncomment to show debug messages
#define CAYENNE_PRINT Serial  // Comment this out to disable prints and save space
#include <CayenneMQTTEthernetW5500.h>
#include "max6675.h"

int thermoDO = 4;
int thermoCS = 5;
int thermoCLK = 6;
MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "802d7b80-1a7d-11ea-b301-fd142d6c1e6c";
char password[] = "af656f1e5b502f452de13a1b87a53840a5a4d8a5";
char clientID[] = "c32d6760-f87b-11ea-883c-638d8ce4c23d";

void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
}

void loop() {
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
// You can also use functions for specific channels, e.g CAYENNE_OUT(1) for sending channel 1 data.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here. This example just sends the current uptime in milliseconds on virtual channel 0.
  Cayenne.virtualWrite(0, millis());

  Cayenne.celsiusWrite(1, thermocouple.readCelsius());
  //Cayenne.virtualWrite(2, thermocouple.readFahrenheit());
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}
