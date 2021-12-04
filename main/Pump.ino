
#define PUMP 8
#define WaterLevelSensor A2


void initPump(){
  pinMode(PUMP, OUTPUT);

  digitalWrite(PUMP, LOW);
  delay(500);
  digitalWrite(PUMP, HIGH);
}

void forcePump(){
  Serial.println(" -------Water On ------- ");
  digitalWrite(PUMP, LOW);
  delay(4000);
  digitalWrite(PUMP, HIGH);
  Serial.println(" ------- Water Off ------- ");
}
