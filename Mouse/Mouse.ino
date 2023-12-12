#include <Mouse.h>

const int XAXIS = A0;
const int YAXIS = A1;
const int SW = 13;
const int VELOCITY = 10;

void setup() {
  pinMode(SW, INPUT);
  Mouse.begin();
}

void loop() {
  int xMove = analogRead(XAXIS);
  int yMove = analogRead(YAXIS);
  int click = digitalRead(SW);

  if (yMove > 500 && yMove < 510) {
    yMove = 513;
  }

  int xShift = map(xMove, 0, 1023, -VELOCITY, VELOCITY);
  int yShift = map(yMove, 0, 1023, VELOCITY, -VELOCITY);

  Mouse.move(yShift, xShift, 0);

  if (click == LOW) {
    Mouse.click();
    delay(50);  
  }

  delay(10);

}
