#include <Servo.h>

// Arduino pin assignment
#define PIN_SERVO 10

// configurable parameters
#define _DUTY_MIN 453 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1476 // servo neutral position (90 degree)
#define _DUTY_MAX 2399 // servo full counterclockwise position (180 degree)

#define _POS_START (_DUTY_MIN + 100  )
#define _POS_MID (_DUTY_NEU )
#define _POS_END (_DUTY_MAX - 100 )

#define _SERVO_SPEED 3  // servo speed limit (unit: degree/second)
#define INTERVAL 340  // servo update interval

// global variables
unsigned long last_sampling_time; // unit: ms
int duty_chg_per_interval; // maximum duty difference per interval
int toggle_interval, toggle_interval_cnt;
float pause_time; // unit: sec
Servo myservo;
int duty_target, duty_curr;
int count;//counting for setting duty_target

void setup() {
// initialize GPIO pins
  myservo.attach(PIN_SERVO); 
  duty_target = duty_curr = _POS_START;
  myservo.writeMicroseconds(duty_curr);
  
// initialize serial port
  Serial.begin(57600);

// convert angle speed into duty change per interval.
  duty_chg_per_interval = (float)(_DUTY_MAX - _DUTY_MIN) * _SERVO_SPEED / 180 * INTERVAL / 1000;


// initialize variables for servo update.
  pause_time = 1;
  toggle_interval = (180.0 / _SERVO_SPEED + pause_time) * 1000 / INTERVAL;
  toggle_interval_cnt = toggle_interval;
  
// initialize last sampling time
  last_sampling_time = 0;
 // initialize count about setting duty_target
  count = 0;
}

void loop() {
// wait until next sampling time. 
// millis() returns the number of milliseconds since the program started. Will overflow after 50 days.
  if(millis() < last_sampling_time + INTERVAL) return;

// adjust duty_curr toward duty_target by duty_chg_per_interval
  if(duty_target > duty_curr) {
    duty_curr += duty_chg_per_interval;
    if(duty_curr > duty_target) duty_curr = duty_target;
  }
  else {
    duty_curr -= duty_chg_per_interval;
    if(duty_curr < duty_target) duty_curr = duty_target;
  }

// update servo position
  myservo.writeMicroseconds(duty_curr);

// output the read value to the serial port
  Serial.print("Min:1000,duty_target:");
  Serial.print(duty_target);
  Serial.print(",duty_curr:");
  Serial.print(duty_curr);
  Serial.println(",Max:2000");
  Serial.println(myservo.read());

// toggle duty_target between _DUTY_MIN and _DUTY_MAX.
  if(toggle_interval_cnt >= toggle_interval) {
    toggle_interval_cnt = 0;
    if (count<2){
        if(duty_target == _POS_START) {
          duty_target = _POS_END;
          count+=1;
        }
        else {
          duty_target = _POS_MID;
          //reset _SERVO_SPEED to 0.3 (unit: degree/second)
          float servo_speed = 0.3;
          duty_chg_per_interval = (float)(_DUTY_MAX - _DUTY_MIN) * servo_speed / 180 * INTERVAL / 1000;
          count+=1;
        }
      }
    else duty_target = _POS_MID;
  }
  else {
    if (count<3) toggle_interval_cnt++;
    else toggle_interval_cnt=0;//stop servo to _POS_MID
  }

// update last sampling time
  last_sampling_time += INTERVAL;
}
