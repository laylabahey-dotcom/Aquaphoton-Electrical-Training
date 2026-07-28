//TIMER
int time_start;
int time_now;
int time_diff;

//BUZZER
int buzzpin = 11;

//USER INPUT FOR MODE, RGB COLORING
int Rpin = 13;
int Gpin = 2;
int Bpin = 12;
String mode;

//SHOWING SEQUENCE LED
int redled = 7;
int yellowled = 8;
int greenled = 9; 
int blueled = 10;

//INPUT BUTTONS
int redbutton = 3;
int yellowbutton =  4;
int greenbutton =  5;
int bluebutton = 6;

//MODE SETTINGS
int ingamedelay;
int easydelay = 3000;
int mediumdelay = 1500;
int harddelay = 750;

int ingamecount;
int easycount = 4;
int mediumcount = 6;
int hardcount = 8;

// INITIALISE LED SEQUENCE 
//0 = Red, 1 = Yellow, 2 = Green, 3 = Blue
int ledseq[] = {0, 3, 2, 1, 0, 2, 3, 1};
int ledPins[] = {7, 8, 9, 10};   
int buttonPins[] = {3, 4, 5, 6};

//SCORE 
int score = 0;


void setup() {
  Serial.begin(9600);
  //RGB LED
  pinMode(Rpin, OUTPUT);
  pinMode(Bpin, OUTPUT);
  pinMode(Gpin, OUTPUT);
  //4 SEQUENCE LEDs
  pinMode(redled, OUTPUT);
  pinMode(yellowled, OUTPUT);
  pinMode(greenled, OUTPUT);
  pinMode(blueled, OUTPUT);
  //4 USER BUTTONS
  pinMode(redbutton, INPUT_PULLUP);
  pinMode(yellowbutton, INPUT_PULLUP);
  pinMode(greenbutton, INPUT_PULLUP);
  pinMode(bluebutton, INPUT_PULLUP);
}

void loop() {
  //ASK FOR MODE OF GAME, AKA LENGTH and SPEED OF GAME
  //RGB SHOW MODE
  Serial.println("Choose Mode (easy-green/medium-blue/hard-red): ");
  while(Serial.available()==0){}
  mode = Serial.readString();
  mode.trim();
  if(mode == "easy"){
    digitalWrite(Gpin, HIGH);
    digitalWrite(Bpin, LOW);
    digitalWrite(Rpin, LOW);
    ingamecount = easycount;
    ingamedelay = easydelay;
  } 
  else if(mode == "medium"){
    digitalWrite(Rpin, LOW);
    digitalWrite(Gpin, LOW);
    digitalWrite(Bpin, HIGH);
    ingamecount = mediumcount;
    ingamedelay = mediumdelay;
  }
  else if(mode == "hard"){
    digitalWrite(Rpin, HIGH);
    digitalWrite(Bpin, LOW);
    digitalWrite(Gpin, LOW);
    ingamecount = hardcount;
    ingamedelay = harddelay;
  }
  else {
    Serial.println("Invalid selection. Try again.");
    return;
  }
  
  
  //SHOW PATTERN TO PLAYER
  for(int i = 0; i< ingamecount; i++){
    int brightLed = ledPins[ledseq[i]];
    digitalWrite(brightLed, HIGH);
    delay(ingamedelay);
    digitalWrite(brightLed, LOW);
    delay(200);
  }
  
  Serial.println("Now, it's your turn to press the sequence!");
  int fail = 0;
  
  
  //DELAY MEASUREMENT
  time_start = millis();
  
  //USER INPUT
  for(int j = 0; j < ingamecount; j++){
    int expectedbutton = buttonPins[ledseq[j]];
    int pressedbutton = -1;
     while (pressedbutton == -1) { //no buttons have been pressed
       time_now = millis();
       time_diff = time_now-time_start;
      if (time_diff == 5000) {
        Serial.println("Too long! Game startover!");
        tone(buzzpin, 300, 1000);
        
        // Reset RGB & restart game
        digitalWrite(Rpin, LOW);
        digitalWrite(Gpin, LOW);
        digitalWrite(Bpin, LOW);
        break; 
      }
       if (digitalRead(redbutton) == LOW)    pressedbutton = redbutton;
       if (digitalRead(yellowbutton) == LOW) pressedbutton = yellowbutton;
       if (digitalRead(greenbutton) == LOW)  pressedbutton = greenbutton;
       if (digitalRead(bluebutton) == LOW)   pressedbutton = bluebutton;
  }
    if(pressedbutton != expectedbutton){
      fail = 1;
      break;
    }
    else{
      int matchingled = ledPins[ledseq[j]];
      digitalWrite(matchingled, HIGH);
      delay(200);
      digitalWrite(matchingled, LOW);
      delay(200);
      while (digitalRead(pressedbutton) == LOW) {}
    }
  }
  
  //GAME RESULTS
  if(fail){
    Serial.println("Game over!");
    tone(buzzpin, 300, 1000); //tone(pin, frequency, duration)
  }
  else{
    Serial.println("Sucess! Game Won!");
    tone(buzzpin, 1000, 400); 
    score++;
  }
  
  //SCORE DISPLAY
  Serial.print("Score: ");
  Serial.println(score);
  
  //ClEAR RGB LED
  digitalWrite(Rpin, LOW);
  digitalWrite(Gpin, LOW);
  digitalWrite(Bpin, LOW);
  delay(2000);
  
}


