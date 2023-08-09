#include <Arduino.h>
#include <TimerOne.h>

#define T    2 

const float Diameter = 0.51; float lnTime = 0;
long endTime=0; long startTime; int lin_vel=0;
int RPM = 0; long lastDebounceTime = 0; int lastInputState = LOW;        

void setup() {
  Serial.begin(9600);
  pinMode(T, INPUT);
} 
 
void loop() {
  int currentSwitchState = digitalRead(T);
  if (currentSwitchState != lastInputState && currentSwitchState==1 ) {
    lastDebounceTime = millis();
    calculateRPM();
    timerIsr();
     delay(150);
  }
  lastInputState = currentSwitchState;
}

void calculateRPM() {
  startTime = lastDebounceTime;
  lnTime = startTime - endTime;
  RPM = 60000 / lnTime; 
  endTime = startTime;
}

void timerIsr() {
  // RPM 계산
  lin_vel = (Diameter  * PI ) * RPM * 60 / 1000 ;
  Serial.print("Linear Speed: ");
  Serial.println(lin_vel);
}
