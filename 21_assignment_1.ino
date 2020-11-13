// Arduino pin assignment
#include <Servo.h>
#define PIN_SERVO 10
#define PIN_IR A0
#define PIN_LED 9
#define _DUTY_NEU 1435
#define _DIST_ALPHA 0.9


//global variables
int a, b; // unit: mm
Servo myservo;
float dist_ema,alpha;



void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
// initialize serial port
  Serial.begin(57600);
  a = 70;
  b = 280;
  alpha = _DIST_ALPHA;
  myservo.attach(PIN_SERVO);
  myservo.writeMicroseconds(_DUTY_NEU);
}
float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}
void loop() {
  float raw_dist = ir_distance();
  dist_ema = alpha*raw_dist + (1-alpha)*raw_dist;//ema filter
  float dist_cali = 100 + 300.0 / (b - a) * (dist_ema - a);
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  // 공의 위치 275mm일때 측정한 거리(dist_cali): 238
  if(dist_cali > 238){
    myservo.writeMicroseconds(_DUTY_NEU-279);
    delay(100);
  }
  else {
    myservo.writeMicroseconds(_DUTY_NEU+270);
    delay(100);
  }

}
