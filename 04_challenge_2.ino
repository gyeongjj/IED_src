
int ledPin = 7; //LED connected to digital pin 7
int Num=0;
int Period=0;
float duty=0;
void setup() {
 // nothing happens in setup
 pinMode(ledPin,OUTPUT);//analog output
}

void loop() {
  Num+=1;
  Period = set_period(Num);//Period값 설정
  int Power=1;
  for (duty = 0; duty <= 100; duty = set_duty(Power,Period)){
    digitalWrite(ledPin,0);
    delayMicroseconds(Period*(duty*(0.01)));//duty값만큼 켜진채로 대기
    digitalWrite(ledPin,1);
    delayMicroseconds(Period*(1-(duty*(0.01))));//duty값만큼 꺼진채로 대기
  }
  Power=0;
  for (duty =100; duty>=0; duty = set_duty(Power,Period)){
    digitalWrite(ledPin,0);
    delayMicroseconds(Period*(duty*(0.01)));//duty값만큼 꺼진채로 대기
    digitalWrite(ledPin,1);
    delayMicroseconds(Period*(1-(duty*(0.01))));//duty값만큼 꺼진채로 대기
  }
  if (Num==3){
    Num=0;//Num 값을 초기화
  }
  delay(2000);//wait for 2 seconds before change Period
}
int set_period(int num){
  int time;
  if (num==1){
    time = 10000; //Period값을 10000us로 설정
  }
  else if (num==2){
    time = 1000; //Period값을 1000us로 설정
  }
  else {
    time = 100; //Period값을 100us로 설정
  }
  return time;
}
float set_duty(int power,int Period ){
  if (power == 1){
    if (Period = 10000){
      duty+=1; //duty값 변화량을 1%로 설정하고 1%올림
    }
    else if (Period = 1000){
      duty+=0.2;//duty값 변화량을 0.2%로 설정하고 0.2%올림
    }
    else{
      duty+=0.02;//duty값 변화량을 0.02%로 설정하고 0.02%올림
    }
       
  }
  else {
    if (Period = 10000){
      duty-=1;//duty값 변화량을 1%로 설정하고 1%내림
    }
    else if (Period = 1000){
      duty-=0.2;//duty값 변화량을 0.2%로 설정하고 0.2%내림
    }
    else{
      duty-=0.02;//duty값 변화량을 0.02%로 설정하고 0.02%내림
    }
  }   
   return duty;
}
