#include "SoftwareSerial.h"
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver srituhobby = Adafruit_PWMServoDriver();

#define servo1 0
#define servo2 1
#define servo3 2
#define servo4 3

#define trig 10
#define echo 11
unsigned long duration; // biến đo thời gian
int distance;  

int SignalPin = A0 ;  // khai báo chân cảm biến hồng ngoại
int Object;

int relay = 4; // điều khiên động cơ băng tải

int estimate_distance();
void handle_hold_item(int value1, int value2);

void setup()
{
  pinMode(SignalPin, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
  pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
  srituhobby.begin();
  srituhobby.setPWMFreq(60);
  delay(3000);
  Serial.begin(9600);
}

void loop()
{ 
  Object = analogRead(SignalPin);
  if (Object > 1000 && Object < 1280)
  {
    digitalWrite(relay, LOW); // băng tải chạy

  }
  else if(Object > 18 && Object < 25)
  {
    distance = estimate_distance();
    if(distance >= 3.1 && distance <= 5){

      delay(2000);
      digitalWrite(relay, HIGH);
      handle_hold_item(760, 0);

    }else if(distance <= 2.9){
      
      delay(2000);
      digitalWrite(relay, HIGH);
      handle_hold_item(400, 760);

    }
  }
}

int estimate_distance(){

    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    duration = pulseIn(echo,HIGH);  
    return ((duration/2)*0.034 );

}

void handle_hold_item(int value1, int value2){
  for (int S1value = value1; S1value < value2; S1value++)
  {
    srituhobby.setPWM(servo1, 0, S1value);
    delay(3);
  }
  for (int S2value = 150; S2value <= 380; S2value++)
  {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(3);
  }
  delay(2000);
  for (int S3value = 380; S3value > 100; S3value--)
  {
    srituhobby.setPWM(servo3, 0, S3value);
    delay(1);
  }
  for (int S2value = 380; S2value > 150; S2value--)
  {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(3);
  }
  delay(1000);

  
  for (int S1value = value2; S1value >= value1; S1value--)
  {
    srituhobby.setPWM(servo1, 0, S1value);
    delay(3);
  }
  for (int S2value = 150; S2value <= 380; S2value++)
  {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(3);
  }
  delay(800);
  for (int S4value = 300; S4value <= 400; S4value++)
  {
    srituhobby.setPWM(servo4, 0, S4value);
    delay(4);
  }
  for (int S3value = 10; S3value < 380; S3value++)
  {
    srituhobby.setPWM(servo3, 0, S3value);
    delay(1);
  }
  delay(2000);
  for (int S4value = 400; S4value > 300; S4value--)
  {
    srituhobby.setPWM(servo4, 0, S4value);
    delay(4);
  }
  for (int S2value = 380; S2value > 150; S2value--)
  {
    srituhobby.setPWM(servo2, 0, S2value);
    delay(3);
  }

}