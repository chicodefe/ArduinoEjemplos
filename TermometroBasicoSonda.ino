/*
 Name:		TermometroBasicoSonda.ino
 Created:	11/27/2016 6:17:42 PM
 Author:	Chicodefe
*/
//Librerias para sensor de temperatura
#include <OneWire.h>
#include <DallasTemperature.h>
//Librerias para Display
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
OneWire oneWire_Pin(4);
DallasTemperature sensorSonda(&oneWire_Pin);
// the setup function runs once when you press reset or power the board
void setup()
	{
	// start serial port
	Serial.begin(9600);
	// Start up the library
	sensorSonda.begin();
	}
// the loop function runs over and over again until power down or reset
void loop()
	{
	sensorSonda.requestTemperatures();
	Serial.print("Temperatura: ");
	Serial.println(sensorSonda.getTempCByIndex(0));
	delay(10000);
	}
