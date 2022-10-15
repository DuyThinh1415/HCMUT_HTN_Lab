#include <Arduino.h>
#include <string.h>

#define LED 2

int printTime = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED, OUTPUT);

}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
  Serial.print("Hello World: print ");
  Serial.print(printTime);
  Serial.println(" times");
  printTime++;
}
