#include <AccelStepper.h>
#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

DS3231 myRTC;
LiquidCrystal_I2C lcd(0x27, 16, 2); 

#define motorPin1 4
#define motorPin2 0
#define motorPin3 2
#define motorPin4 15
#define MotorInterfaceType 4

bool century = false;
bool h12Flag;
bool pmFlag;
byte alarmDay, alarmHour, alarmMinute, alarmSecond, alarmBits;
bool alarmDy, alarmH12Flag, alarmPmFlag;
String waktu;

const int cahaya = 34;
const int air = 35;

AccelStepper stepper = AccelStepper(MotorInterfaceType, motorPin1, motorPin3, motorPin2, motorPin4);
const int bawah=0;
const int atas=1024;



void setup() {
    pinMode(cahaya, INPUT);
    pinMode(air, INPUT);
    stepper.setMaxSpeed(500);
    stepper.setAcceleration(900);
    Serial.begin(9600);
    Wire.begin();

    //rtc.begin();
    lcd.begin();
    lcd.setCursor(0,0);
      lcd.print("   Welcome To");
    lcd.setCursor(0,1);
      lcd.print("Jemuran Otomatis");
    delay(1000);
    lcd.clear();
}

void loop() {
  if(digitalRead (cahaya)==0 && digitalRead(air)==1){
    stepper.runToNewPosition(10050); 
    }
  else{
    stepper.runToNewPosition(0); 
    }
  
  lcd.setCursor(0,0);
  lcd.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  lcd.print(" ");
  lcd.print(myRTC.getMinute(), DEC);
  lcd.print(" ");
  lcd.print(myRTC.getSecond(), DEC);
    
  if (myRTC.getHour(h12Flag, pmFlag)==8 && myRTC.getMinute()==00){
    stepper.runToNewPosition(10050);
  }
  else if (myRTC.getHour(h12Flag, pmFlag)==16 && myRTC.getMinute()==00){
    stepper.runToNewPosition(0);
  }
    
//    waktu = String(myRTC.getHour(h12Flag, pmFlag), DEC)+" "+ 
//            String(myRTC.getMinute(), DEC)+" "+
//            String(myRTC.getSecond(), DEC);
//     if(waktu=="08:00:00"){
//      stepper.runToNewPosition(10050);
//  }
//     else if (waktu=="16:00:00"){
//      stepper.runToNewPosition(0);
//  }

  
  // to see time in serial monitor
  Serial.print(myRTC.getHour(h12Flag, pmFlag), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getMinute(), DEC);
  Serial.print(" ");
  Serial.print(myRTC.getSecond(), DEC);

  // Display the temperature
  Serial.print("T=");
  Serial.print(myRTC.getTemperature(), 2);
  lcd.setCursor(0,1);
  lcd.print("Suhu: ");
  lcd.print(myRTC.getTemperature(), 2);
    
 }
