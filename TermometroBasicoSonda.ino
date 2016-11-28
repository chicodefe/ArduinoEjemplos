/*
 Name:		TermometroBasicoSonda.ino
 Created:	11/27/2016 6:17:42 PM
 Author:	Chicodefe
*/


#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS_1 2
#define ONE_WIRE_BUS_2 4

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_inhouse(&oneWire_in);
DallasTemperature sensor_outhouse(&oneWire_out);

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	Serial.println("Dallas Temperature Control Library Demo - TwoPin_DS18B20");
	sensor_inhouse.begin();
	sensor_outhouse.begin();
	Serial.print("Found ");
	Serial.print(sensor_inhouse.getDeviceCount(), DEC);
	Serial.print(sensor_outhouse.getDeviceCount(), DEC);
	Serial.println(" devices.");
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.print("Requesting temperatures...");
	sensor_inhouse.requestTemperatures();
	sensor_outhouse.requestTemperatures();
	Serial.println(" done");
	Serial.print("Inhouse: ");
	Serial.println(sensor_inhouse.getTempCByIndex(0));
	Serial.print("Outhouse: ");
	Serial.println(sensor_outhouse.getTempCByIndex(0));
	delay(1000);
}
