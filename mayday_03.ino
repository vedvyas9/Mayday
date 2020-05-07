
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2,3);//RX,TX

const int buttonOne=8;
const int buttonTwo=9;
const int buttonThree=10;
const int buttonFour=11;


const int read = A0; //Sensor AO pin to Arduino pin A0
int value;          //Variable to store the incomming data


int buttonLastState1=0;
int buttonLastState2=0;
int buttonLastState3=0;
int buttonLastState4=0;
int buttonPushCounter1=0;
int buttonPushCounter2=0;
int buttonPushCounter3=0;
int buttonPushCounter4=0;
int buttonState1=0;
int buttonState2=0;
int buttonState3=0;
int buttonState4=0;


void setup() {
  mySerial.begin(9600);
  pinMode(buttonOne, INPUT);
  pinMode(buttonTwo, INPUT);
  pinMode(buttonThree, INPUT);
  pinMode(buttonFour, INPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState1 = digitalRead(buttonOne);
  buttonState2 = digitalRead(buttonTwo);
  buttonState3 = digitalRead(buttonThree);
  buttonState4 = digitalRead(buttonFour);

  if(buttonState1 != buttonLastState1) {//WORKING ON BUTTON 2 FOR GSM CODE BLUE
    if(buttonState1 == HIGH) {
       buttonPushCounter1++;
       mySerial.println("AT+CMGS=\"+918013984974\"\r");
       delay(700);
       mySerial.println("Code Blue!");
       delay(100);
       mySerial.println((char)26);
       delay(700);
    } else {
      delay(10);
    }
    delay(20);
  }
  if(buttonState2 != buttonLastState2) {//WORKING ON BUTTON 2 FOR GSM CODE BLUE
    if(buttonState2 == HIGH) {
       buttonPushCounter2++;
       mySerial.println("AT+CMGS=\"+919641805409\"\r");
       delay(700);
       mySerial.println("Code Red!");
       delay(100);
       mySerial.println((char)26);
       delay(700);
    }
    else {
    delay(10);
    }
    delay(20);
  }
  if(buttonState3 != buttonLastState3) {//WORKING ON BUTTON 2 FOR GSM CODE BLUE
    if(buttonState3 == HIGH) {
      buttonPushCounter3++;
       mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Code Yellow!");
       delay(100);
       mySerial.println((char)26);
       delay(700);
    } else {
      delay(10);
    }
    delay(20);
  }
  if(buttonState4 != buttonLastState4) {//WORKING ON BUTTON 2 FOR GSM CODE BLUE
    if(buttonState4 == HIGH) {
      buttonPushCounter4++;
       mySerial.println("AT+CMGS=\"+919641805409\"\r");
       delay(700);
       mySerial.println("Code Orange!");
       delay(100);
       mySerial.println((char)26);
       delay(700);
    } else {
      delay(10);
    }
    delay(20);
  }

  int sensorValue = analogRead(A0);
  Serial.print(sensorValue);
  if( sensorValue>700){
    mySerial.println("AT+CMGS=\"+919381636674\"\r");
    delay(700);
    mySerial.println("smoke detected");
    delay(100);
    mySerial.println((char)26);
    delay(5000);
  }


  value = analogRead(read); //Read data from analog pin and store it to value variable
  
  if (value<=480){ 
    Serial.println("Water level: 0mm");
  }
  else if (value>480 && value<=530){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 0mm to 5mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  }
  else if (value>530 && value<=615){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 5mm to 10mm");
       delay(100);
       mySerial.println((char)26);
       delay(700); 
  }
  else if (value>615 && value<=660){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 10mm to 15mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  } 
  else if (value>660 && value<=680){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 15mm to 20mm");
       delay(100);
       mySerial.println((char)26);
       delay(700); 
  }
  else if (value>680 && value<=690){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 20mm to 25mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  }
  else if (value>690 && value<=700){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 25mm to 30mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  }
  else if (value>700 && value<=705){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 30mm to 35mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  }
  else if (value>705){ 
    mySerial.println("AT+CMGS=\"+917901066620\"\r");
       delay(700);
       mySerial.println("Water level: 35mm to 40mm");
       delay(100);
       mySerial.println((char)26);
       delay(700);
  }
  
  delay(5000); // Check for new value every 5 sec

  
  buttonLastState1=buttonState1;
  buttonLastState2=buttonState2;
  buttonLastState3=buttonState3;
  buttonLastState4=buttonState4;
}
