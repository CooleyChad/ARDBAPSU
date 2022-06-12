//Alex Cooley
//Updated 6/12/2022
//Arduino Based Power Supply Unit
//ARDBAPSU Version 1.1
//Configuration 1.4

#include <Wire.h> //I2C Library
#include <LiquidCrystal_I2C.h> //LCD I2C Library
#include <Adafruit_INA260.h> //I2C INA260 Library
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD addressw to 0x27 for a 20 chars and 4 line display
Adafruit_INA260 ina260 = Adafruit_INA260();


const int analogInput0 = A0; //pin for Voltage Divider Module

const int Alarm = 10; //pin for ATtiny85 Alarm Enable
const int Relay = 11; //pin for Relay that shuts off when the battery is charged

float R1 = 33090.0; //value of R1
float R2 = 9950.0; //value of R2

void setup(){

 //pin intialization
  
  pinMode(analogInput0, INPUT);
  pinMode(Relay, OUTPUT);
  pinMode(Alarm, OUTPUT);

  ina260.begin();
  
   lcd.begin();                   
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(6,1);
  lcd.print("Welcome");
  delay(2500);

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("Arduino");
  lcd.setCursor(7,1);
  lcd.print("Based");
  lcd.setCursor(7,2);
  lcd.print("Power");
  lcd.setCursor(7,3);
  lcd.print("Supply");
  delay(2500);
  
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(6,1);
  lcd.print("ARDBAPSU");
  lcd.setCursor(4,2);
  lcd.print("Version 1.3");
  delay(2500);

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(6,0);
  lcd.print("Designed");
  lcd.setCursor(9,1);
  lcd.print("By");
  lcd.setCursor(6,2);
  lcd.print("Alexander");
  lcd.setCursor(7,3);
  lcd.print("Cooley");
  delay(2500);

  digitalWrite(Alarm,HIGH);

  lcd.clear();
  lcd.backlight();
  lcd.setCursor(7,1);
  lcd.print("Alarm");
  lcd.setCursor(7,2);
  lcd.print("Test");
  delay(5000);

  digitalWrite(Relay, HIGH);
  digitalWrite(Alarm, LOW);
}
void loop(){
  // read the value at analog input
   
   float Value0 = 00.0; //A0 Voltage Divider Module
   
   
   
   Value0 = analogRead(analogInput0); //A0 Voltage Divider Module
 
   
   //calculations

   float VIN = 0.0;
   float adc_Voltage0 = 0.0;
   int ref_Voltage0 = 5.07;

  float VOUT = 0.00;
   
   adc_Voltage0 = (Value0 * ref_Voltage0) / 1024.0; 
   VIN =  adc_Voltage0 / (R2/(R1+R2)); //A0 Voltage Divider Module

   VOUT = ina260.readBusVoltage() / 1000;


   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Voltage: ");
   lcd.setCursor(10,0);
   lcd.print(VOUT);
   lcd.setCursor(0,1);
   lcd.print("mA");
   lcd.setCursor(11,1);
   lcd.print(ina260.readCurrent());
   lcd.setCursor(0,2);
   lcd.print("Input: ");
   lcd.setCursor(10,2);
   lcd.print(VIN);
   delay(1000);
   

   if(ina260.readCurrent()>= 4500){
    digitalWrite(Alarm,HIGH);
    digitalWrite(Relay, LOW);
    delay(1000);
   }
   else{
    digitalWrite(Alarm,LOW);
    digitalWrite(Relay,HIGH);
   }
   
}
