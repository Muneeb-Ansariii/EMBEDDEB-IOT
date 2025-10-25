//NAME: MUNEEB ANSARI
//TITLE: TASK-2
//ROLL NO: 1270


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pin numbers
#define LED_PIN 18
#define BUZZER_PIN 27
#define BUTTON_PIN 14

// Variables
unsigned long pressTime = 0;   // to store when button was pressed
bool buttonPressed = false;    // to check if button is being pressed
bool ledState = false;         // to store LED ON/OFF state

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button connected to GND

  // Initialize OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(10, 25);
  display.println("System Ready");
  display.display();
  delay(1000);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);

  // When button is pressed (LOW)
  if (buttonState == LOW && !buttonPressed) {
    pressTime = millis();       // store the time when pressed
    buttonPressed = true;
  }

  // When button is released
  if (buttonState == HIGH && buttonPressed) {
    unsigned long pressDuration = millis() - pressTime;  // calculate how long it was pressed
    buttonPressed = false;

    display.clearDisplay();
    display.setCursor(10, 25);

    if (pressDuration < 1500) {
      // Short press → toggle LED
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
      display.println("Short Press");
      display.setCursor(10, 40);
      display.println(ledState ? "LED ON" : "LED OFF");
    } else {
      // Long press → play buzzer
      display.println("Long Press");
      display.setCursor(10, 40);
      display.println("Buzzer ON");
      tone(BUZZER_PIN, 1000);   // 1kHz tone
      delay(1000);
      noTone(BUZZER_PIN);
      display.setCursor(10, 55);
      display.println("Buzzer OFF");
    }

    display.display();
  }
}
