#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
float value = 0;
int soilMoisturePin = A0;
int pumpMotor = D4; 

//----------- Enter you Wi-Fi Details---------//

char ssid[] = "SAI GUNAKAR"; // your network SSID (name)
char pass[] = "saiteja1319"; // your network password

//-------------------------------------------//
//----------- Channel Details -------------//

unsigned long Channel_ID =1229756 ; // Channel ID
const int Field_number = 1; // Don't change
const char * WriteAPIKey = "VKAY8YD3T9HJDB0H"; // Your write API Key
  

// ----------------------------------------//

WiFiClient client;
void setup()
{
 Serial.begin(115200);
 while(!Serial){;}
 WiFi.mode(WIFI_STA);
 ThingSpeak.begin(client);
}
void loop()
{
 internet();
 get_value();
 upload();
}

void internet()
{
 if (WiFi.status() != WL_CONNECTED)
 {
 Serial.print("Attempting to connect to SSID: ");
 Serial.println(ssid);
 while (WiFi.status() != WL_CONNECTED)
 {
 WiFi.begin(ssid, pass);
 Serial.print(".");
 delay(5000);
 }
 Serial.println("\nConnected.");
 }
}

void get_value()
{
 int moistureReading = analogRead(soilMoisturePin);
 value = moistureReading;
  Serial.print("MoistureLevel : ");
  Serial.println(moistureReading); 
  delay(2000);
    if(moistureReading > 600){
    digitalWrite(pumpMotor,HIGH);
    Serial.println("SOIL IS DRY");
    Serial.println("PUMP MOTOR IS ON");
    
  }
   else if(moistureReading > 350){
    digitalWrite(pumpMotor,LOW);
    Serial.println("SOIL IS WET");
    Serial.println("PUMP MOTOR IS OFF");
  }
  else if(moistureReading > 200 ){
    digitalWrite(pumpMotor,LOW);
    Serial.println("SOIL IS FULLY WATERED");
  }
    
}
void upload()
{
 internet();
 ThingSpeak.writeField(Channel_ID, Field_number, value, WriteAPIKey);
 Serial.println("data updated to thingspeak");
 delay(15000);
}
