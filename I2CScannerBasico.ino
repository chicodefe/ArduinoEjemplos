/*
 Name:		I2CScannerBasico.ino
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

	while(!Serial)
		{
		}
	//Print on Serial
	Serial.println();
	Serial.println("I2C scanner. Scanning ...");
	byte count=0;
	Wire.begin();
	for(byte i=1; i<120; i++)
		{
		Wire.beginTransmission(i);
		if(Wire.endTransmission()==0)
			{
			//Print on Serial
			Serial.print("Found address: ");
			Serial.print(i,DEC);
			Serial.print(" (0x");
			Serial.print(i,HEX);
			Serial.println(")");
			count++;
			// delay in between reads for stability
			delay(1);
			} // end of good response
		} // end of for loop

	//Print on Serial
	Serial.println("Done.");
	Serial.print("Found ");
	Serial.print(count,DEC);
	Serial.println(" device(s).");

	//Parametros LCD
	lcd.begin(20,4); // initialize the lcd for 16 chars 2 lines, turn on backlight
	lcd.setCursor(0,0);
	lcd.print("Iniciando...");
	delay(300);
	lcd.setCursor(0,1);
	lcd.print("Listo");
	delay(300);
	lcd.clear();
	}// end of setup

void loop()// the loop function runs over and over again until power down or reset
	{
	//Print on LCD
	lcd.setCursor(0,0); //Start at character 0 on line 0
	lcd.print("Pantalla");
	lcd.setCursor(0,1); //Start at character 0 on line 2
	lcd.print("Lista");
	delay(1000);
	lcd.clear();
	delay(500);
	}// end of for loop