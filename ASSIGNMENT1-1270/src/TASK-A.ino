//NAME : MUNEEB ANSARI
//TITLE : TASK 1
//ROLL NO : 1270



#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define LED1 18
#define LED2 19
#define BUTTON_MODE 14
#define BUTTON_RESET 27

int mode = 0;
bool lastModeState = HIGH;
bool lastResetState = HIGH;
unsigned long lastPressTime = 0;
const unsigned long debounceDelay = 200;

void showMode() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.print("Mode: ");
  display.println(mode);

  if (mode == 0) display.println("Both OFF");
  else if (mode == 1) display.println("Alternate Blink");
  else if (mode == 2) display.println("Both ON");
  else if (mode == 3) display.println("PWM Fade");

  display.display();
}

void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  pinMode(BUTTON_RESET, INPUT_PULLUP);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  showMode();
}

void loop() {
  bool modeState = digitalRead(BUTTON_MODE);
  bool resetState = digitalRead(BUTTON_RESET);

  // ---- Handle Mode Button ----
  if (modeState == LOW && lastModeState == HIGH && millis() - lastPressTime > debounceDelay) {
    lastPressTime = millis();
    mode = (mode + 1) % 4;
    showMode();
  }

  // ---- Handle Reset Button ----
  if (resetState == LOW && lastResetState == HIGH && millis() - lastPressTime > debounceDelay) {
    lastPressTime = millis();
    mode = 0; // back to off
    showMode();
  }

  lastModeState = modeState;
  lastResetState = resetState;

  // ---- LED Behavior ----
  switch (mode) {
    case 0: // both off
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      break;

    case 1: // alternate blink
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, LOW);
      delay(300);
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, HIGH);
      delay(300);
      break;

    case 2: // both on
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      break;

    case 3: // fade
      for (int i = 0; i <= 255; i++) {
        analogWrite(LED1, i);
        delay(5);
      }
      for (int i = 255; i >= 0; i--) {
        analogWrite(LED1, i);
        delay(5);
      }
      break;
  }
}
