/*
  Name:		TermometroBasicoSonda.ino
  Created:	11/27/2016 6:17:42 PM
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

//Parametros Display
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3,POSITIVE);// Set the LCD I2C address

//Parametros Libreria OneWire
OneWire oneWire_Pin(4);// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
//Parametros Libreria DallasTemperature
DallasTemperature sensorSonda(&oneWire_Pin);// Pass our oneWire reference to Dallas Temperature.

void setup()// the setup function runs once when you press reset or power the board
	{
	//Parametros Pines
	pinMode(4,INPUT); // sets the digital pin 4 as input

	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second

	//Parametros LCD
	lcd.begin(20,4); // initialize the lcd for 16 chars 2 lines, turn on backlight
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

	//Parametros Sensores
	sensorSonda.begin();// Iniciando el Sensor

	//Verificacion do Sensores
	if(sensorSonda.getDeviceCount()==0)
		{
		Serial.println("Sensor no Conectado");
		lcd.setCursor(0,0); //Start at character 0 on line 0
		lcd.print("Sensor ");
		lcd.setCursor(0,1); //Start at character 0 on line 2
		lcd.print("no Conectado");
		delay(1000);
		lcd.clear();
		delay(100);
		return;
		}

	//Solicitudes de Temperatura
	sensorSonda.requestTemperatures();

	//Print on Serial	
	Serial.print("Temperatura: ");
	Serial.print(sensorSonda.getTempCByIndex(0));
	Serial.print((char)223);
	Serial.println(" Celsius");

	//Print on LCD
	lcd.setCursor(0,0); //Start at character 0 on line 0
	lcd.print("Temperatura: ");
	lcd.setCursor(0,1); //Start at character 0 on line 2
	lcd.print(sensorSonda.getTempCByIndex(0));
	lcd.print((char)223);
	lcd.print(" Celsius");
	delay(10000);
	lcd.setCursor(0,1); //Start at character 0 on line 2
	lcd.print("                ");
	}// end of for loop