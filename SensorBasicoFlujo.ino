/*
Name:		TermometroBasicoSonda.ino
Created:	11/27/2016 6:17:42 PM
Author:	Chicodefe
*/

volatile int NumPulsos; //variable para la cantidad de pulsos recibidos
int PinSensor=2;    //Sensor conectado en el pin 2

void ContarPulsos()//---Funci�n que se ejecuta en interrupci�n
	{
	NumPulsos++;  //incrementamos la variable de pulsos
	}


int ObtenerFrecuencia()//---Funci�n para obtener frecuencia de los pulsos
	{
	int frecuencia;
	NumPulsos=0;   //Ponemos a 0 el n�mero de pulsos
	interrupts();    //Habilitamos las interrupciones
	delay(1000);   //muestra de 1 segundo
	noInterrupts(); //Desabilitamos las interrupciones
	frecuencia=NumPulsos; //Hz(pulsos por segundo)
	return frecuencia;
	}

void setup()
	{
	Serial.begin(9600);
	pinMode(PinSensor,INPUT);
	attachInterrupt(0,ContarPulsos,RISING); //(Interrupcion 0(Pin2),funcion,Flanco de subida)
	}

void loop()
	{
	int frecuencia=ObtenerFrecuencia(); //obtenemos la Frecuencia de los pulsos en Hz

	Serial.print("FrecuenciaPulsos: ");//-----Enviamos por el puerto serie---------------
	Serial.println(frecuencia);
	if(frecuencia==0)
		{
		Serial.println("Inactivo");
		}
	else
		{
		Serial.println("Activado");
		}
	}

