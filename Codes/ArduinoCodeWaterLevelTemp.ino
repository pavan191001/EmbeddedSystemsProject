// ---------- declaration ---------------

#include <SoftwareSerial.h>
String str; //------ for transfering data to nodemcu
SoftwareSerial espSerial(5, 6);
const int buzzer = 9;
int sensorPin = A1;
int tempPin = A0;
int flag=0;
// ----------  setup function --------------

void setup(){
  Serial.begin(115200);
  espSerial.begin(115200);                 
  pinMode(sensorPin,INPUT);
  pinMode(buzzer,OUTPUT); 
  pinMode(tempPin,INPUT);
  delay(200);
}

//------- loop function ----------------

void loop()                     
{
  flag =0;
  //------------- Temperature --------------------
      int reading = analogRead(tempPin);  
 
 float voltage = reading *(5/1024.0);
 
 
 float temperatureC = voltage* 100 ;  //converting from volts to temp
 flag=1;
 if(flag == 1){
  str = String(1);
  espSerial.println(str);
  str =String("data from arduino: ")+String("Temperature ")+String(temperatureC);
  espSerial.println(str);
 }
 Serial.print("Temperature :");
 Serial.print(temperatureC); 
 Serial.println(" degrees C");
 delay(3000); 

//-------------- WaterLevel Sensor With Buzzer and transfering to nodemcu ---------------------

int waterLevel = analogRead(sensorPin);
str =String("data from arduino: ")+String("Water level ")+String(waterLevel);
espSerial.println(str);
Serial.println("WaterLevel is: ");
Serial.println(waterLevel);
delay(4000);
  if(waterLevel<300){
  Serial.println("Water tank is empty");
  str =String("data from arduino: ")+String("Water tank is empty ");
  espSerial.println(str);
  tone(buzzer, 1000);
  delay(1000);        
  noTone(buzzer);     
  delay(1000);        
  }
   else if(waterLevel<615){
    str =String("data from arduino: ")+String("Water tank is 1/2 empty ");
    espSerial.println(str);   
    Serial.println("Water tank is 1/2 empty");    
  }
  else if(waterLevel<660){
      str =String("data from arduino: ")+String("Water tank is full ");
      espSerial.println(str);
      Serial.println("Water tank is full");    
  }
delay(5000);
}
