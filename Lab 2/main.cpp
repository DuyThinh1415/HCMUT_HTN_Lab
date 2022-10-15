#include <Arduino.h>
#include <string.h>

#define LED 2



class MutexLock
{

  public:
    void lock(){
      counter = 10;
      _lock = true;
    }

    bool isLock(){
      return _lock;
    }

    void interupTimer(){
      if (_lock){
        counter--;
        if (counter <= 0){
          counter = 0;
          _lock = false;
        }
      }
    }
  private:
    bool _lock = false;
    int counter = 0;  
};

MutexLock mutexLock4button;

hw_timer_t *My_timer = NULL;

bool toggleValue = 0;
int isrTime = 0;
char stringBuff[8];


void IRAM_ATTR isr(){
  if (!mutexLock4button.isLock()){
    mutexLock4button.lock();
    toggleValue != toggleValue;
    isrTime++;
    itoa(isrTime,stringBuff,8);
    Serial.println("run isr");
    Serial.println(isrTime);
  }
}

void IRAM_ATTR onTimer(){
  mutexLock4button.interupTimer();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(18,INPUT_PULLUP);
  attachInterrupt(18,isr, FALLING);

  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 100000, true);
  timerAlarmEnable(My_timer);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH);
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
}
