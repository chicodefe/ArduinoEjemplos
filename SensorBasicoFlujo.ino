/*
Name:		TermometroBasicoSonda.ino
Created:	11/27/2016 6:17:42 PM
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

volatile long NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor=2;    //Sensor conectado en el pin 2
int tiempoReset=0;

void ContarPulsos()//---Función que se ejecuta en interrupción
	{
	NumPulsos++;  //incrementamos la variable de pulsos
	}

int ObtenerFrecuencia()//---Función para obtener frecuencia de los pulsos
	{
	int frecuencia;
	NumPulsos=0;   //Ponemos a 0 el número de pulsos
	interrupts();    //Habilitamos las interrupciones
	delay(1000);   //muestra de 1 segundo
	noInterrupts(); //Desabilitamos las interrupciones
	frecuencia=NumPulsos; //Hz(pulsos por segundo)
	return frecuencia;
	}

void setup()// the setup function runs once when you press reset or power the board
	{

	//Parametros Pines
	pinMode(PinSensor,INPUT); // sets the digital pin 2 as input

	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second

	attachInterrupt(digitalPinToInterrupt(2),ContarPulsos,CHANGE); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
	}

void loop()// the loop function runs over and over again until power down or reset
	{
	int frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz


	Serial.print("Pulsos por Segundo: ");//-----Enviamos por el puerto serie---------------
	Serial.println(frecuencia);

	if(frecuencia!=0)
		{
		tiempoReset=5;
		}
	else if(frecuencia==0&&tiempoReset>0)
		{
		tiempoReset=--tiempoReset;
		}

	if(tiempoReset>0)
		{
		Serial.print("Activado ");
		Serial.println(tiempoReset);
		}
	else
		{Serial.println("Inactivo ");
	
	}
	}