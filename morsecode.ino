int greenpin = 11;
int time_unit = 300;
String encoded;

void setup()
{
  Serial.begin(9600);
  pinMode(greenpin, OUTPUT);
}

void loop()
{
  Serial.println("Enter encoded message: ");
  while(Serial.available() == 0){}
  encoded = Serial.readString();
  
  for(int i = 0; i < encoded.length(); i++){
    //Dots
    if(encoded[i] == '.'){
      digitalWrite(greenpin, HIGH);
      delay(time_unit);
      digitalWrite(greenpin, LOW);
      delay(time_unit); //Pause between letters
    }
    //Dashes
    else if(encoded[i] == '-'){
	  digitalWrite(greenpin, HIGH);
      delay(3*time_unit);
      digitalWrite(greenpin, LOW);
      delay(time_unit); //Pause between letters
    }
    //Spaces between letters
    else if(encoded[i] == ' '){
      delay(2*time_unit); //3-1=2 time units, compensated in dashes and dots
    }
    //Spaces between words
    else if(encoded[i] == '/'){
      delay(6*time_unit); //7-1=6 time units, compensated in dashes and dot
    }
  }
}
  
