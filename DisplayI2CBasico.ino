/*
  Name:		DisplayI2CBasico.ino
  Created:	11/27/2016 10:34:34 PM
  Author:	Chicodefe
*/

//Librerias para Serial
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

//Librerias para Display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Parametros Display
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3,POSITIVE); // Set the LCD I2C address

void setup()// the setup function runs once when you press reset or power the board
	{
	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second

	//Parametros LCD
	lcd.begin(20,4); // initialize the lcd for 20 chars 4 lines, turn on backlight
	lcd.backlight();
	delay(300);
	lcd.noBacklight();
	delay(300);
	lcd.backlight();
	lcd.setCursor(0,0);
	lcd.print("Iniciando");
	delay(300);
	lcd.setCursor(0,1);
	lcd.print("Listo");
	delay(300);
	// Wait and then tell user they can start the Serial Monitor and type in characters to
	// Display. (Set Serial Monitor option to "No Line Ending")
	lcd.clear();

	//Print on LCD
	lcd.setCursor(0,0); //Start at character 0 on line 0
	lcd.print("Use Serial Mon");
	lcd.setCursor(0,1);
	lcd.print("Type to display");
	}// end of setup

void loop()// the loop function runs over and over again until power down or reset
	{
			{
			// when characters arrive over the serial port...
			if(Serial.available())
				{
				// wait a bit for the entire message to arrive
				delay(100);
				// clear the screen
				lcd.clear();
				// read all the available characters
				while(Serial.available()>0)
					{
					// display each character to the LCD
					lcd.write(Serial.read());
					}
				}
			}
	}// end of for loop