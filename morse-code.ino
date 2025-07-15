// C++ code
//
const int button = 2;
const int ledPin = 13;
const int ledPin2 = 12;
const int ledPin3 = 11;
const int ledPin4 = 10;
int lastButtonState = LOW;
int buttonState = LOW;
bool buttonOn = false;
const int buzzer = 3;
int signalLength = 0;
int minSignalLength = 30;
int longSignalLength = 300;
int pauseLength = 450;
int spacePauseLength = 1500;
int lowDelay = 0;
int pause = 0;
bool checker;
String dash = "-";
String morse = "";
String dot = "*";

void setup(){
    pinMode(button, INPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(buzzer, OUTPUT);
    Serial.begin(9600);
}

void loop(){
  buttonState = digitalRead(button);
  if (buttonState == HIGH){
    lowDelay = 0;
    buttonOn = true;
  }else{
    lowDelay += 1;
    if (lowDelay >= minSignalLength){
      lowDelay = 0;
      buttonOn = false;
    }
  }  
  if (buttonOn){    
    signalLength += 1;
    if(signalLength < longSignalLength){
      tone(buzzer, 1500);
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin2, LOW);
    }
    else{
      tone(buzzer, 800);
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin2, HIGH);      
    }
    pause = 0;         
  }else{ 
    noTone(buzzer);
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    if (signalLength >= minSignalLength){
      checker = true;
      if (signalLength < longSignalLength)
        morse = morse + dot;
      else
        morse = morse + dash;  
    }        
    signalLength = 0;  
    pause += 1;
    if (pause > pauseLength && morse != ""){
      checkForLetters();
      digitalWrite(ledPin3, HIGH);
      delay(50);
      digitalWrite(ledPin3, LOW);   
      morse = "";
    }
    if (pause > spacePauseLength){
        if (checker){
          morse = " ";
          checkForLetters();
          digitalWrite(ledPin4, HIGH);
          delay(50);
          digitalWrite(ledPin4, LOW);          
          checker = false;
        }
        pause = 0;
    }
  }
  delay(1);
}

void checkForLetters(){

   int check;

   char* MORSE[27] = {
    " ","*-", "-***", "-*-*", "-**", "*", "**-*", "--*", "****", "**", // A-I
    "*---", "-*-", "*-**", "--", "-*", "---", "*--*", "--*-", "*-*", // J-R
    "***", "-", "**-", "***-", "*--", "-**-", "-*--", "--**" // S-Z
    };

    String LETTERS[27] = {
    " ","A","B","C","D","E","F","G","H","I","J","K","L","M",
    "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

    for (int i=0; i<27; i++){
      if (morse==MORSE[i]){
          check = i;
          break;
      } else {
          check = 0;
      }
    }
    Serial.print (LETTERS[check]);
}




