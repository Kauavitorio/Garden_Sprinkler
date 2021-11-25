
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

int pushbutton = A0;
int forceWork_btn = A1;

//  Main Led Infdi
int red_light_pin= 4;
int green_light_pin = 3;
int blue_light_pin = 2;

//  Methods extern from other classes
extern void checkTemperature();
extern void initDHT();
extern void initPump();
extern void forcePump();
extern void RGB_color();
extern void initTimer();
extern void getTimer();

long baseDELAY = 250;
long dhtDELAY = 10000;
long current_DHT_DELAY = 0;

void setup() {
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baudrate speed
  
  Serial.println("------ Garden Sprinkler");
  Serial.println("------ By Kaua Vitorio");
  Serial.println("------ Github: https://github.com/Kauavitorio");
  Serial.println("------ DHT11 Humidity & temperature Sensor");
  Serial.println("------ Relé 1 Canal 5v");
  Serial.println("------ Starting up system ------\n\n");
  
  initDHT();
  initPump();
  initTimer();
  pinMode(pushbutton, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(forceWork_btn, INPUT_PULLUP); // define o pino do botao como entrada
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  RGB_color(0, 0, 0); // White
}

void loop() {
 
  if (digitalRead(pushbutton) == LOW) // If the mode button is pressed
  { 
  
    RGB_color(255, 0, 0); // Red
    delay(1000);
    RGB_color(0, 255, 0); // Green
    delay(1000);
    RGB_color(0, 0, 255); // Blue
    delay(1000);
    RGB_color(255, 255, 125); // Raspberry
    delay(1000);
    RGB_color(0, 255, 255); // Cyan
    delay(1000);
    RGB_color(255, 0, 255); // Magenta
    delay(1000);
    RGB_color(255, 255, 0); // Yellow
    delay(1000);
    RGB_color(255, 255, 255); // White
    delay(1000);
  }
  
  if (digitalRead(forceWork_btn) == LOW) // If the force pump button is pressed
  { 
    forcePump();
  }

  if(current_DHT_DELAY >= dhtDELAY){
    current_DHT_DELAY = 0;
    checkTemperature();
    getTimer();   
  }else current_DHT_DELAY = current_DHT_DELAY + (5 + baseDELAY);



  
   // Wait a few seconds between measurements:
   delay(baseDELAY);

}
