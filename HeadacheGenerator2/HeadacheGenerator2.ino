  #include <SPI.h>
  #include <Wire.h>
  #include <Adafruit_GFX.h>
  #include <Adafruit_SSD1306.h>
  #include <EEPROM.h>

#define BUZZER_PIN 2

#define OLED_MOSI 9
#define OLED_CLK 10
#define OLED_DC 11
#define OLED_CS 12
#define OLED_RESET 13

const char *minutesBuffer = calloc(2, sizeof(char));
const char *secondsBuffer = calloc(2, sizeof(char));

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  display.begin();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
}

void loop() {

  for (int secondsLast = 10; secondsLast >= 0; secondsLast--) {

    tone(BUZZER_PIN, 8000);

    sprintf(minutesBuffer, "%02d", secondsLast / 60);
    sprintf(secondsBuffer, "%02d", secondsLast % 60);

    display.clearDisplay();
    display.invertDisplay(false);
    display.setCursor(15, 5);
    display.print(String(minutesBuffer) + ":" + String(secondsBuffer));
    display.display();

    noTone(BUZZER_PIN);
    delay(1000UL);
  }


  display.clearDisplay();
  display.setCursor(15, 5);
  display.print(++EEPROM[20]);
  display.invertDisplay(true);
  display.display();
  
  tone(BUZZER_PIN, 3000, 1000UL * 20);

}
