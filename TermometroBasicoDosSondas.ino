/*
 Name:		TermometroBasicoDosSondas.ino
 Created:	11/28/2016 12:59:59 AM
 Author:	Chicodefe
*/
//Librerias para Serial
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
//Librerias para sensor de temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
//Librerias para Display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

OneWire oneWire_Pin(4);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3,POSITIVE);// Set the LCD I2C address
DallasTemperature sensorSonda(&oneWire_Pin);
void setup()// the setup function runs once when you press reset or power the board
	{
  pinMode(4, INPUT);// sets the digital pin 4 as input
	Serial.begin(9600);// initialize serial communication at 9600 bits per second
	sensorSonda.begin();// Iniciando el Sensor
	lcd.begin(16,2);// initialize the lcd for 16 chars 2 lines, turn on backlight
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

	}// end of setup
void loop()// the loop function runs over and over again until power down or reset
	{
	sensorSonda.requestTemperatures();
	Serial.print("Temperatura: ");
	Serial.print(sensorSonda.getTempCByIndex(0));
	Serial.print("�");
	Serial.println(" Celsius");

	lcd.setCursor(0,0); //Start at character 0 on line 0
	lcd.print("Temperatura: ");
	lcd.setCursor(0,1);//Start at character 0 on line 2
	lcd.print(sensorSonda.getTempCByIndex(0));
	lcd.print((char)223);
	lcd.print(" Celsius");
	delay(10000);
	lcd.clear();
	}// end of for loop
