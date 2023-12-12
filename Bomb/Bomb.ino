const int LED_A = 5;
const int LED_B = 6;
const int LED_C = 9;
const int LED_D = 8;
const int LED_E = 7;
const int LED_F = 4;
const int LED_G = 3;
const int LED_DP = 10;

const int LED_PINS[] = {
  LED_A,
  LED_B,
  LED_C,
  LED_D,
  LED_E,
  LED_F,
  LED_G,
  LED_DP
};


const int DIGIT_1[] = { 3, LED_B, LED_C, LED_DP };
const int DIGIT_2[] = { 6, LED_A, LED_B, LED_G, LED_E, LED_D, LED_DP };
const int DIGIT_3[] = { 6, LED_A, LED_B, LED_G, LED_C, LED_D, LED_DP };
const int DIGIT_4[] = { 5, LED_F, LED_B, LED_G, LED_C, LED_DP };
const int DIGIT_5[] = { 6, LED_A, LED_F, LED_G, LED_C, LED_D, LED_DP };
const int DIGIT_6[] = { 7, LED_A, LED_F, LED_G, LED_C, LED_D, LED_E, LED_DP };
const int DIGIT_7[] = { 4, LED_A, LED_B, LED_C, LED_DP };
const int DIGIT_8[] = { 8, LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, LED_G, LED_DP };
const int DIGIT_9[] = { 7, LED_A, LED_B, LED_C, LED_D, LED_F, LED_G, LED_DP };
const int DIGIT_0[] = { 7, LED_A, LED_B, LED_C, LED_D, LED_E, LED_F, LED_DP };


const int RELE_PIN = 2;

const int *DIGITS_ORDER[] = {
  DIGIT_9, DIGIT_8, DIGIT_7, DIGIT_6, DIGIT_5, DIGIT_4, DIGIT_3, DIGIT_2, DIGIT_1, DIGIT_0
};

const int DIGITS_ORDER_SIZE = 10;

int current_digit_index = 0;



void displayDigit(int *digit) {

  for (int i = 0; i < 8; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }

  for (int i = 1; i <= digit[0]; i++) {
    digitalWrite(digit[i], HIGH);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(RELE_PIN, OUTPUT);
  for (int i = 0; i < sizeof(LED_PINS) / sizeof(LED_PINS[0]); i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop() {
  delay(1000);
  digitalWrite(RELE_PIN, HIGH);
  displayDigit(DIGITS_ORDER[current_digit_index]);
  current_digit_index += 1;
  if (current_digit_index >= DIGITS_ORDER_SIZE) {
    current_digit_index = 0;
  }
  delay(1000);
  digitalWrite(RELE_PIN, LOW);
}
