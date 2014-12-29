/*
  LiquidCrystal Library - Hello World
 
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
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 25 July 2009
 by David A. Mellis
 modified 2012-2014 and beyond for temp control
 by Jonathan H. Williams
 
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>
 #include <math.h>
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin = Target temp +
const int buttonPin2 = 8;     // the number of the pushbutton pin = Target temp -
const int actionPin =  9;      // the number of the LED pin
const int backlightPin =  13;      // LCD Backlight

// Steinhart-Hart Thermistor Equation
double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}


// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonPushCounter = 40;   // counter for the number of button presses
int status = 0;

void setup() {
 // initialize the LED pin as an output:
  pinMode(backlightPin, OUTPUT);   
// initialize the LED pin as an output:
  pinMode(actionPin, OUTPUT);  
  // initialize the first pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize the second pushbutton pin as an input:
  pinMode(buttonPin2, INPUT);
  
{
  digitalWrite(backlightPin, HIGH);
   }
{
  Serial.begin(9600);
   
   // set up the LCD's number of rows and columns: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("The Artisans'");
  lcd.setCursor(1, 1);
  lcd.print("Cold Controller");
  
  digitalWrite(backlightPin, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(backlightPin, HIGH);    // turn the LED off by making the voltage LOW
  delay(2000);               // wait for a second
  
  
  lcd.begin(16, 2);
  
  lcd.print("Actual Temp:");
  
  lcd.setCursor(0, 1);
  
  lcd.print("Target Temp:");
  
}

}
void loop() {
  
 
     // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  buttonState2 = digitalRead(buttonPin2);
    
  // read the analog input into a variable:
      int reading = (Thermistor(analogRead(0)));

   // print the result:
  Serial.println(reading);
   // wait 10 milliseconds for the analog-to-digital converter
   // to settle after the last reading:
   delay(350);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(12, 0);
  // print the number of seconds since reset:
  lcd.println(reading);
  
    lcd.setCursor(14, 0);
    
  lcd.print((char)223);
  
  lcd.print("F");

 
if (buttonState != LOW)
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter++;
      
       lcd.setCursor(12, 1);
      lcd.println(buttonPushCounter, DEC);
       lcd.setCursor(14, 1);
      lcd.print((char)223);
    lcd.print("F");
  
      delay(10);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      lcd.println("40"); 
    }
          
if (buttonState2 != LOW)
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState2 == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:
      buttonPushCounter--;
      
     lcd.setCursor(12, 1);
      lcd.println(buttonPushCounter, DEC);
       lcd.setCursor(14, 1);
      lcd.print((char)223);
    lcd.print("F");
    
      delay(10);
    } 
    else {
      // if the current state is LOW then the button
      // wend from on to off:
      lcd.println("40"); 
    }
    
    if(reading > buttonPushCounter+4){
  status = 1;
  }

if (reading < buttonPushCounter-4){
  status = 0;
  }

if (status == 1){
  digitalWrite(actionPin, HIGH);
  delay(10000);
   }
  
  

if (status == 0){
  digitalWrite(actionPin, LOW);
    }
  
   
 
}

