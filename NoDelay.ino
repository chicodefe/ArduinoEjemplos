/*
 Name:		NoDelay.ino
 Created:	12/3/2016 1:28:41 AM
 Author:	Chicodefe
*/

/* Blink without Delay

Turns on and off a light emitting diode (LED) connected to a digital
pin, without using the delay() function.  This means that other code
can run at the same time without being interrupted by the LED code.

The circuit:
* LED attached from pin 13 to ground.
* Note: on most Arduinos, there is already an LED on the board
that's attached to pin 13, so no hardware is needed for this example.

This example code is in the public domain.

http://www.arduino.cc/en/Tutorial/BlinkWithoutDelay
*/

//Librerias para Serial
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

int ledState = LOW;// ledState used to set the LED

				 // Generally, you should use "unsigned long" for variables that hold time. The value will quickly become too large for an int to store
unsigned long previousMillis1 = 0;// millis() returns an unsigned long.
unsigned long intervalMillis1 = 1000; // the time we need to wait
unsigned long time;

void setup()// the setup function runs once when you press reset or power the board
{
	//Parametros Pines
	pinMode(13, OUTPUT);// sets the digital pin 4 as input

					   //Parametros Serial
	Serial.begin(9600);// initialize serial communication at 9600 bits per second
}

void loop()// the loop function runs over and over again until power down or reset
{
	//Asignar el tiempo desde transcurrido
	unsigned long currentMillis = millis();

	if (currentMillis - previousMillis1 >= intervalMillis1)
	{
		// save the last time you blinked the LED
		previousMillis1 = currentMillis;

		// if the LED is off turn it on and vice-versa:
		if (ledState == LOW)
		{
			ledState = HIGH;
		}
		else
		{
			ledState = LOW;
		}

		// set the LED with the ledState of the variable:
		digitalWrite(13, ledState);
	}
	Serial.print("Time: ");
	time = millis();
	//prints time since program started
	Serial.println(time);
	// wait a second so as not to send massive amounts of data
	//delay(100);
}
