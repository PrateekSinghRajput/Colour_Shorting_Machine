#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Servo.h>
Servo pickServo;
Servo dropServo;

#define S0 4 
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8    
int frequency = 0;
int color=0;

int detectColor() {
  // activating red photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);

   // activating blue photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  
  // activating green photodiodes to read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);

  delay(50);

  if(R<1190 & R>950& G<1310 & G>1180){
    color = 1; 
    Serial.print("Detected Color is = ");
    Serial.println("BLUE");
    lcd.clear();
    lcd.print("Detected Color");
    lcd.setCursor(0,5);
    lcd.print("BLUE");
  }
  if(G<1190 & G>1010 & R<950 & R>750){
    color = 2; 
     Serial.print("Detected Color is = ");
      Serial.println("YELLOW");
       lcd.clear();
    lcd.print("Detected Color");
    lcd.setCursor(0,5);
    lcd.print("YELLOW");
  }
  if(R<990& R>800 &     B<1000 & B>850){
    color = 3;
      Serial.print("Detected Color is = ");
    Serial.println("GREEN");
     lcd.clear();
    lcd.print("Detected Color");
    lcd.setCursor(0,5);
    lcd.print("GREEN");
  }

  if (G<1500 & G>1300 & B<1150 & B>900){
    color = 5; 
     Serial.print("Detected Color is = ");
    Serial.println("RED");
     lcd.clear();
    lcd.print("Detected Color");
    lcd.setCursor(0,5);
    lcd.print("RED");
  }
  return color;  
}

void setup() {
   
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.begin(16,2);
    lcd.print("Colour Shorting");
    lcd.setCursor(0,1);
    lcd.print("by Prateek");
    delay(2000);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //frequency-scaling to 20% selected
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  pickServo.attach(9);
  dropServo.attach(10);

  Serial.begin(9600);
}

void loop() {
  //initial position of servo motor
  pickServo.write(115);
  delay(600);
  
  for(int i = 115; i > 65; i--) {
    pickServo.write(i);
    delay(2);
  }
  delay(500);
  //read color values by calling function. save the values for conclusion in variable
  color = detectColor();
  delay(1000);  

  switch (color) {
    case 1:
    dropServo.write(20);
    
    break;

    case 2:
    dropServo.write(40);
    break;

    case 3:
    dropServo.write(60);
    break;

    case 5:
    dropServo.write(80);
    break;
    
    case 0:
    break;
  }
  delay(500);
  
  for(int i = 65; i > 29; i--) {
    pickServo.write(i);
    delay(2);
  } 
  delay(300);
  
  for(int i = 29; i < 115; i++) {
    pickServo.write(i);
    delay(2);
  }
  color=0;
}
