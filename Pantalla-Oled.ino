
//Librerias para Arduino
#include <Arduino.h>

//Librerias para Comunicacion Serial
#include <SoftwareSerial.h>
#include <api/HardwareSerial.h>

//Librerias para I2C
#include <Wire.h>

//Librerias para Pantalla Grafica
#include <U8g2lib.h>
#include <U8x8lib.h>

//Constructor para Pantalla Grafica Oled
U8G2_SSD1305_128X64_ADAFRUIT_F_HW_I2C u8g2(U8G2_MIRROR, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ 9);

void setup() {
  //Iniciar Pantalla
  u8g2.begin();
}
void loop(void) {

  u8g2.clearBuffer();
  u8g2.setFlipMode(1);
 

  u8g2.firstPage();
  do {
 u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());

  
    
   //   u8g2.drawPixel(0, 0);

 u8g2.setFont(u8g2_font_ncenB14_tr);
 u8g2.setCursor(3, 17);
u8g2.print("Hello World!");
  } while ( u8g2.nextPage() );
  delay(1000);
}
