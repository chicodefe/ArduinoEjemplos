/*
 Name:		SensorFlujoNoDelay.ino
 Created:	12/2/2016 10:33:58 AM
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

int ciclo=0;
int frecuencia=0;

//Parametros Sensor de flujo
volatile long NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor=2;    //Sensor conectado en el pin 2
int tiempoReset=0;

//Parametros DelayMillis
// Generally, you should use "unsigned long" for variables that hold time. The value will quickly become too large for an int to store

unsigned long currentMillis1;
unsigned long currentMillis2;
unsigned long time;

unsigned long previousMillis1=0;// millis() returns an unsigned long.
unsigned long intervalMillis1=1000; // the time we need to wait

unsigned long previousMillis2=0;// millis() returns an unsigned long.
unsigned long intervalMillis2=1000; // the time we need to wait

void ContarPulsos()//---Función que se ejecuta en interrupción
	{
	NumPulsos++;  //incrementamos la variable de pulsos
	}

int ObtenerFrecuencia()//---Función para obtener frecuencia de los pulsos
	{interrupts();//Habilitamos las interrupciones
	Serial.println("Obtener Frecuencia");
	Serial.print("millis()=");
	Serial.println(millis());
	Serial.print("currentMillis1=");
	Serial.println(currentMillis1);
	Serial.print("previousMillis1=");
	Serial.println(previousMillis1);
	Serial.print("NumPulsos=");
	Serial.println(NumPulsos);
	Serial.print("frecuencia=");
	Serial.println(frecuencia);
	Serial.println("");

	if(currentMillis1-previousMillis1>=1)
		{
		
		Serial.println("Iniciamos Interrupciones");
		Serial.print("millis()=");
		Serial.println(millis());
		Serial.print("currentMillis1=");
		Serial.println(currentMillis1);
		Serial.print("previousMillis1=");
		Serial.println(previousMillis1);
		Serial.print("NumPulsos=");
		Serial.println(NumPulsos);
		Serial.print("frecuencia=");
		Serial.println(frecuencia);
		Serial.println("");

		}

	if(currentMillis1-previousMillis1>=100)
		{
		noInterrupts(); //Desabilitamos las interrupciones
		frecuencia=NumPulsos; //Hz(pulsos por segundo)
		NumPulsos=0;   //Ponemos a 0 el número de pulsos

		Serial.println("Terminamos Interrupciones");
		Serial.print("millis()=");
		Serial.println(millis());
		Serial.print("currentMillis1=");
		Serial.println(currentMillis1);
		Serial.print("previousMillis1=");
		Serial.println(previousMillis1);
		Serial.print("NumPulsos=");
		Serial.println(NumPulsos);
		Serial.print("frecuencia=");
		Serial.println(frecuencia);
		Serial.println("");

		previousMillis1=currentMillis1;

		Serial.println("Igualamos los millis");
		Serial.print("millis()=");
		Serial.println(millis());
		Serial.print("currentMillis1=");
		Serial.println(currentMillis1);
		Serial.print("previousMillis1=");
		Serial.println(previousMillis1);
		Serial.print("NumPulsos=");
		Serial.println(NumPulsos);
		Serial.print("frecuencia=");
		Serial.println(frecuencia);
		Serial.println("");
		


		}


	Serial.println("Final Obtener Frecuencia");
	Serial.print("millis()=");
	Serial.println(millis());
	Serial.print("currentMillis1=");
	Serial.println(currentMillis1);
	Serial.print("previousMillis1=");
	Serial.println(previousMillis1);
	Serial.print("NumPulsos=");
	Serial.println(NumPulsos);
	Serial.print("frecuencia=");
	Serial.println(frecuencia);


return frecuencia;
	}

void setup()// the setup function runs once when you press reset or power the board
	{


	//Parametros Pines
	pinMode(PinSensor,INPUT); // sets the digital pin 2 as input

	//Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second


	Serial.println("Inicio Programa");



	attachInterrupt(digitalPinToInterrupt(2),ContarPulsos,CHANGE); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
	}

void loop()// the loop function runs over and over again until power down or reset
	{
	ciclo=++ciclo;
	Serial.print("Inicio Ciclo=");
	Serial.println(ciclo);
	Serial.print("millis()=");
	Serial.println(millis());
	Serial.println("");


	currentMillis1=millis();//Asignar el tiempo desde transcurrido
	currentMillis2=millis();//Asignar el tiempo desde transcurrido

	int frecuencia=ObtenerFrecuencia();//obtenemos la Frecuencia de los pulsos en Hz

	Serial.print("ObtenerFrecuencia()=");
	Serial.println(frecuencia);
	Serial.println("");
	Serial.println("");


	if(frecuencia!=0)

		{
		Serial.print("Pulsos por Segundo: ");//Enviamos por el puerto serie
		Serial.println(frecuencia);
		}


	if(frecuencia!=0)//obtenemos la Frecuencia de los pulsos en Hz
		{
		tiempoReset=5;//fijamos en 5 loops el tiempo
		}
	else if(frecuencia==0&&tiempoReset>0)
		{
		if(currentMillis2-previousMillis2>=intervalMillis2)

			previousMillis2=currentMillis2;// save the last time
		{tiempoReset=--tiempoReset;//quitamos 1 loop al tiempo
		}
		}

	if(tiempoReset>0)
		{//Codigo cuando se detecta flujo
		Serial.print("Activado ");
		Serial.println(tiempoReset);
		Serial.print("NumPulsos=");
		Serial.println(NumPulsos);
		Serial.print("frecuencia=");
		Serial.println(frecuencia);

		}
	else
		{//Codigo cuando no se detecta flujo
		Serial.println("Inactivo");
		Serial.println("");
		}


	Serial.print("millis()=");
	Serial.println(millis());
	Serial.println("Final Ciclo");
	Serial.println("delay(1)");
	Serial.println("***************************************************************************");
	Serial.println("");
	Serial.println("");
	Serial.println("");

	delay(1);
	}