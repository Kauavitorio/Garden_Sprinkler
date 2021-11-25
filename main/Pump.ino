
#define PUMP 8
#define WaterLevelSensor A2


void initPump(){
  pinMode(PUMP, OUTPUT);

  digitalWrite(PUMP, LOW);
  delay(500);
  digitalWrite(PUMP, HIGH);
}

void forcePump(){

  digitalWrite(PUMP, LOW);
  delay(1000);
  digitalWrite(PUMP, HIGH);
  delay(1000);
  digitalWrite(PUMP, LOW);
  delay(1000);
  digitalWrite(PUMP, HIGH);
}
