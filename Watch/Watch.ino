#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#include <RtcDS1302.h>

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13
#define BUTTON_1 2
#define BUTTON_2 3

unsigned int SCREEN_TAB = 0;

const char *stringBuffer = calloc(10, sizeof(char));

typedef struct Button {
  const int pin;
  unsigned long lastPressTime;
} Button;

Button buttons[] =  {
  Button {BUTTON_1},
  Button {BUTTON_2}
};

const char *daysOfWeek[] = {
  "Sun",
  "Mon",
  "Tue",
  "Wed",
  "Thu",
  "Fri",
  "Sat"
};

ThreeWire myWire(SDA, SCL, 7); // IO, SCLK, CE
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
RtcDS1302<ThreeWire> Rtc(myWire);

void displayClock() {
  auto time = Rtc.GetDateTime();

  sprintf(stringBuffer, "%02d:%02d:%02d", time.Hour(), time.Minute(), time.Second());

  display.setTextSize(2);
  display.setCursor(15, 12);
  display.print(stringBuffer);

  display.setTextSize(1);
  display.setCursor(15, 2);
  sprintf(stringBuffer, "%02d/%02d/%d", time.Day(), time.Month(), time.Year());
  display.print(daysOfWeek[time.DayOfWeek()]);
  display.print("   " + String(stringBuffer));

  display.display();
  
}


struct Watch {
  unsigned long long startTime = 0;
  unsigned long long endTime = 0;
  bool isRunning = false;
};
static auto watch = Watch {};
void displayStopwatch() {

  if (digitalRead(buttons[1].pin) == HIGH) {
    if ((millis() - buttons[1].lastPressTime) >= 150UL) {
      watch.isRunning = !watch.isRunning;

      if (watch.isRunning) {
        watch.startTime = millis();
        watch.endTime = watch.startTime;
      }
    }

    
    buttons[1].lastPressTime = millis();
  }

  if (watch.isRunning) {
    watch.endTime = millis();
  }

  unsigned long totalElapsed = watch.endTime - watch.startTime;
  int seconds = (totalElapsed / 1000) % 60;
  int minutes = (totalElapsed / 1000 ) / 60;
  int millis = totalElapsed % 1000;
  display.setTextSize(2);
  display.setCursor(0, 0);
  sprintf(stringBuffer, "%d:%02d:%03d", minutes, seconds, (int) millis);
  display.print(stringBuffer);

  display.setTextSize(1);
  display.setCursor(0, 20);
  display.print(String(totalElapsed));
  display.display();
}


void processSwitchTabButton() {
  if (digitalRead(buttons[0].pin) == HIGH) {
    if ((millis() - buttons[0].lastPressTime) >= 150UL) {
      SCREEN_TAB++;
    }

    buttons[0].lastPressTime = millis();
  }
}


void setup() {
  Serial.begin(9600);
  display.begin();
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.clearDisplay();

  for (int i = 0; i < sizeof(buttons) / sizeof(Button); i++) {
    pinMode(buttons[i].pin, INPUT);
  }
}


void loop() {

  processSwitchTabButton();

  display.clearDisplay();

  switch (SCREEN_TAB) {
    case 0: displayClock(); break;
    case 1: displayStopwatch(); break;
    default: SCREEN_TAB = 0; displayClock();
  }
}
