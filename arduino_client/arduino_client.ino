/*
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte celsius[8] = {
  B11110,
  B10010,
  B10010,
  B11110,
  B00000,
  B00000,
  B00000,
};

void setup() {
  Serial.begin(4800);

  Serial.println("Hi, I am alive!");

  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  lcd.createChar(0, celsius);

  printGui();
}
int i = 0;
void loop() {

  if (Serial.available() >= 3){ 
    
    /*lcd.setCursor(0,0); //FOR TESTING
     while(Serial.available()){
     lcd.print(Serial.read());
     lcd.print(" ");
     }*/
     
    // read the incoming byte:
    char input = char(Serial.read());

    if(input=='C'){  
      lcd.setCursor(12, 0);
      lcd.print("   ");

      byte numberInput= byte(Serial.read());
      lcd.setCursor(1, 0);
      int offset = 2;
      if(numberInput>9){
        offset--;
        if(numberInput>99){
          offset--;
        } 
      } 
      lcd.setCursor(12+offset, 0);
      lcd.print(numberInput);
      lcd.setCursor(15, 0);
      lcd.write(byte(0));
    }
    else if(input=='M'){
      lcd.setCursor(12, 1);
      lcd.print("   ");

      byte numberInput= byte(Serial.read());
      int offset = 2;
      if(numberInput>9){
        offset--;
        if(numberInput>99){
          offset--;
        } 
      } 
      lcd.setCursor(12+offset, 1);
      lcd.print(numberInput);
      lcd.setCursor(15, 1);
      lcd.print("%");
    }
    else{
      Serial.println("IGNORED");
      lcd.setCursor(0, 0);
      lcd.print(Serial.available());

    }
  }
}

void printGui(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("CPU TEMP");

  lcd.setCursor(0, 1);
  lcd.print("RAM USAGE");
}

































