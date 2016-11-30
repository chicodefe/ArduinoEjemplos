/*
 Name:		TermometroBasicoDosSondas.ino
 Created:	11/28/2016 12:59:59 AM
 Author:	Chicodefe
*/

//Librerias para Serial
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

//Librerias para Display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Librerias para sensor de temperatura
#include <OneWire.h>
#include <DallasTemperature.h>

//Parametros Display
LiquidCrystal_I2C lcd(0x3f,2,1,0,4,5,6,7,3,POSITIVE); // Set the LCD I2C address

//Parametros Libreria OneWire
OneWire oneWire_in(4); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire_out(5); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

//Parametros Libreria DallasTemperature
DallasTemperature sensor_in(&oneWire_in);// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensor_out(&oneWire_out);// Pass our oneWire reference to Dallas Temperature.

void setup()// the setup function runs once when you press reset or power the board
	{
	//Parametros Pines
	pinMode(4,INPUT); // sets the digital pin 4 as input
	pinMode(5,INPUT); // sets the digital pin 5 as input

	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second

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

	//Parametros Sensores
	sensor_in.begin();// Iniciando el Sensor
	sensor_out.begin();// Iniciando el Sensor

	//Verificacion do Sensores
	if(sensor_in.getDeviceCount()==0||sensor_out.getDeviceCount()==0)
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
	sensor_in.requestTemperatures();
	sensor_out.requestTemperatures();

	//Print on Serial
	Serial.print("Temperatura In: ");
	Serial.print(sensor_in.getTempCByIndex(0));
	Serial.print((char)223);
	Serial.println(" Celsius");
	Serial.print("Temperatura Out: ");
	Serial.print(sensor_out.getTempCByIndex(0));
	Serial.print((char)223);
	Serial.println(" Celsius");

	//Print on LCD
	lcd.setCursor(0,0); //Start at character 0 on line 0
	lcd.print("Temp IN:  ");
	lcd.print(sensor_in.getTempCByIndex(0));
	lcd.print((char)223);
	lcd.setCursor(0,1); //Start at character 0 on line 2
	lcd.print("Temp OUT: ");
	lcd.print(sensor_out.getTempCByIndex(0));
	lcd.print((char)223);
	delay(1000);
	}// end of for loop