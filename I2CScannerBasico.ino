/*
 Name:		I2CScannerBasico.ino
 Created:	11/27/2016 10:34:34 PM
 Author:	Chicodefe
*/

#include <Wire.h>
// the setup function runs once when you press reset or power the board
void setup()
	{
	// initialize serial communication at 9600 bits per second:
	Serial.begin(9600);
	while(!Serial)
		{
		}
	Serial.println();
	Serial.println("I2C scanner. Scanning ...");
	byte count=0;
	Wire.begin();
	for(byte i=1; i<120; i++)
		{
		Wire.beginTransmission(i);
		if(Wire.endTransmission()==0)
			{
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
	Serial.println("Done.");
	Serial.print("Found ");
	Serial.print(count,DEC);
	Serial.println(" device(s).");
	
	}  // end of setup
// the loop function runs over and over again until power down or reset
void loop()
	{}// end of for loop