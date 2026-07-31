#include <Wire.h>
//temperature variables
double temp;
int temp_reading;
int temp_pin = A0;
int redpin_hot = 6;
int orangepin_med = 9;
int bluepin_cold = 11;
int dt = 400;

//light variables
int light_pin = A1;
int light_reading;

//light intensity comes to 1023, needing 2 bytes
byte data[2]; 

void setup()
{
  Serial.begin(9600);
  pinMode(temp_pin, INPUT);
  pinMode(light_pin, INPUT);
  pinMode(redpin_hot, OUTPUT);
  pinMode(orangepin_med, OUTPUT);
  pinMode(bluepin_cold, OUTPUT);
  
  Wire.begin(8);
  Wire.onRequest(sendData);
}

void loop()
{
  //TEMPERATURE READINGS & DISPLAY
  temp_reading = analogRead(temp_pin);
  temp = (double)temp_reading * 5./1023.;
  temp = temp - 0.5;
  temp = temp * 100;
  Serial.println("Current Temperature: ");
  Serial.print(temp);
  if(temp > 0 && temp <= 15){
  	Serial.println("COLD!");
    digitalWrite(bluepin_cold, HIGH);
    delay(dt);
    digitalWrite(bluepin_cold, LOW);
  }
  else if(temp > 15 && temp <= 30){
    Serial.println("MEDIUM TEMPERATURE!");
    digitalWrite(orangepin_med, HIGH);
    delay(dt);
    digitalWrite(orangepin_med, LOW);
  }
  else if(temp > 30){
    Serial.println("Burning hot!");
    digitalWrite(redpin_hot, HIGH);
    delay(dt);
    digitalWrite(redpin_hot, LOW);
  }
  
  //LIGHT READING & MASTER COMMUNICATION
  light_reading = analogRead(light_pin);
  Serial.print("Light intensity: ");
  Serial.println(light_reading);
  
  data[0] = highByte(light_reading);
  data[1] = lowByte(light_reading);
  
  delay(100);
}

void sendData(){
  Wire.write(data, 2);
}
