
#include <Wire.h>
#include <DHT.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>

int pushbutton = A0;
int forceWork_btn = A1;
int speakerPin = 5;

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
extern void StartEnconderSond();
extern void onSong();

long baseDELAY = 150;
long dhtDELAY = 10000;
String CONTROL_PUMP;
long current_DHT_DELAY = 0;

//  Mode vars
int mode = 0;
int stage01 = 0;
int stage02 = 1;
int stage03 = 2;

void setup() {
  Serial.begin(9600); //  Serial Communication is starting with 9600 of baudrate speed
  
  Serial.println("------ Garden Sprinkler");
  Serial.println("------ By Kaua Vitorio");
  Serial.println("------ Github: https://github.com/Kauavitorio");
  Serial.println("------ DHT11 Humidity & temperature Sensor");
  Serial.println("------ Relé 1 Canal 5v");
  Serial.println("------ Starting up system ------\n\n");
  
  initDHT();
  initPump();
  initTimer();
  StartEnconderSond();
  
  pinMode(pushbutton, INPUT_PULLUP); // sets the mode change button pin
  pinMode(forceWork_btn, INPUT_PULLUP); // sets the pin of the push button to irrigate
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  
  mode = EEPROM.read("modeTAG_Log");
  
  RGB_color(255, 255, 255); // White
  onSong();

  delay(1500);

  checkMode();
  
}

void loop() {
 
  if (digitalRead(pushbutton) == LOW) // If the mode button is pressed
  { 
    if(mode == stage01){
      mode = stage02;
    }else if(mode == stage02){
      mode = stage03;
    }else if(mode == stage03){
      mode = stage01;
    }
    Serial.println("------ Change Mode ------");

    EEPROM.write("modeTAG_Log", mode);
    checkMode();
    
    beep(speakerPin, 880, 100);
    delay(50);
  }
  
  if (digitalRead(forceWork_btn) == LOW) // If the force pump button is pressed
  { 
    forcePump();
  }

  if(current_DHT_DELAY >= dhtDELAY){
    current_DHT_DELAY = 0;
    checkTemperature();
  }else current_DHT_DELAY = current_DHT_DELAY + (5 + baseDELAY);
  
    getTimer();   
  
   // Wait a few seconds between measurements:
   delay(baseDELAY);

}

void checkMode(){
  if(mode == stage01){
    RGB_color(0, 255, 0); // Green
  }else if(mode == stage02){
    RGB_color(0, 0, 255); // Blue
  }else if(mode == stage03){
    RGB_color(255, 0, 0); // Red
  }
}
