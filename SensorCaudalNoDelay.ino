/*
 Name:		SensorCaudalNoDelay.ino
 Created:	12/4/2016 12:29:27 PM
 Author:	Chicodefe
*/

//Librerias para Serial
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

//Declarar Parametros Pines
const int PinSensor = 2;//Sensor conectado en el pin 2
const int ledPin = 13;//Led conectado en el pin 13

//Declarar Variables
int ledState = LOW;// ledState used to set the LED
volatile int movimientoLiquido; //Variable para la cantidad de pulsos recibidos
unsigned long previousMillis1 = 0;//Gardamos el ultimo Delay millis() returns an unsigned long.
const long delayMillis1 = 1000;// Gauardamos el tiempo del delay millis() returns an unsigned long
unsigned long previousMillis2 = 0;//Gardamos el ultimo Delay millis() returns an unsigned long.
const long delayMillis2 = 1000;// Gauardamos el tiempo del delay millis() returns an unsigned long.
unsigned long previousMillis3 = 0;//Gardamos el ultimo Delay millis() returns an unsigned long.
const long delayMillis3 = 1000;// Gauardamos el tiempo del delay millis() returns an unsigned long.

int frecuencia = 0;

//Parametros Sensor de flujo
volatile long NumPulsos; //variable para la cantidad de pulsos recibidos

void DetectarPulsos()//---Funci�n que se ejecuta en interrupci�n
	{
	NumPulsos++;
	movimientoLiquido = 4;  //incrementamos la variable de pulsos
	ledState = HIGH;
	}

int ObtenerPulsos()//---Funci�n para obtener frecuencia de los pulsos
	{
	interrupts();//Habilitamos las interrupciones

	if((unsigned long)(millis() - previousMillis1) >= delayMillis1)
		{
		noInterrupts(); //Desabilitamos las interrupciones	
		frecuencia = NumPulsos; //Hz(pulsos por segundo)
		NumPulsos = 0;//Ponemos a 0 el número de pulsos
		previousMillis1 = millis();
		}
	return frecuencia;
	}

void setup()// the setup function runs once when you press reset or power the board
	{

	//Parametros Pines
	pinMode(PinSensor, INPUT);//sets the digital pin PinSensor as input
	pinMode(ledPin, OUTPUT);//sets the digital pin ledPin as output

	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second
	Serial.println("Inicio Programa");

	//Deteccion de interrupciones
	attachInterrupt(digitalPinToInterrupt(PinSensor), DetectarPulsos, CHANGE);//(Interrupcion PinSensor,funcion,Cambio)
	}

void loop()// the loop function runs over and over again until power down or reset
	{
	int frecuencia = ObtenerPulsos();//obtenemos la Frecuencia de los pulsos en Hz

	if(movimientoLiquido != 0)//Verificamos inicio del flujo
		{
		Serial.print("Activado ");
		Serial.println(movimientoLiquido);
		Serial.print("NumPulsos=");
		Serial.println(NumPulsos);
		ledState = HIGH;
		}

	if((unsigned long)(millis() - previousMillis2) >= delayMillis2)//Verificamos cierre del flujo
		{

		if(movimientoLiquido != 0)
			{
			movimientoLiquido = --movimientoLiquido;
			previousMillis2 = millis();
			}
		if(movimientoLiquido == 0)
			{
			Serial.println("Inactivo");
			ledState = LOW;
			}
		}

	if(frecuencia != 0)//obtenemos la Frecuencia de los pulsos en Hz
		{
		Serial.print("Pulsos por Segundo: ");//Enviamos por el puerto serie
		Serial.println(frecuencia);
		}
	digitalWrite(ledPin, ledState);// set the LED with the ledState of the variable
	}