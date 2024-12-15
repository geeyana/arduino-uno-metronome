// For LCD screen
#include <LiquidCrystal.h>
const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Start BPM at 90
int BPM = 90;

// Timer for LEDs
double timer = 0;

// LED pins
int thisPin = 0;

// Button presses (0 or 1)
int plusOne = 0;
int minusOne = 0;
int plusFive = 0;
int minusFive = 0;
int plusTen = 0;
int minusTen = 0;

void setup() {

  // LCD Screen
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Metronome");
  lcd.setCursor(3, 1);
  lcd.print("BPM:");

  // Set up pins for LEDs
  for (thisPin = 0; thisPin <= 7; thisPin++) {
    pinMode(thisPin, OUTPUT);
  }

  // Set up pins for buttons
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
}

void loop() {

  // Print BPM
  lcd.setCursor(8, 1);
  lcd.print(BPM);

  // Read state of buttons
  plusOne = digitalRead(A0);
  plusFive = digitalRead(A1);
  plusTen = digitalRead(A2);
  minusOne = digitalRead(A3);
  minusFive = digitalRead(A4);
  minusTen = digitalRead(A5);

  // Adjust BPM if button is pressed

  if (plusOne == 0) {
    BPM += 1;
  }

  else if (minusOne == 0) {
    BPM -= 1;
  }

  else if (plusFive == 0) {
    BPM += 5;
  }

  else if (minusFive == 0) {
    BPM -= 5;
  }

  else if (plusTen == 0) {
    BPM += 10;
  }

  else if (minusTen == 0) {
    BPM -= 10;
  }

  // LCD screen refresh
  if (BPM < 100 || BPM < 10) {
    lcd.print("    ");
  }

  // Equation for time that LEDs stay on
  // --> (60 s per min) * (1000 ms per s) * (min per beat) / 7 LEDs = ms per LED
  timer = 1000 / (double)BPM * 60 / 7;

  // LEDS

  // Left to right
  for (thisPin = 0; thisPin <= 6; thisPin++) {
    digitalWrite(thisPin, HIGH);  // On
    delay(timer);                 // Time buffer
    digitalWrite(thisPin, LOW);   // Off
  }

  // Right to left
  for (thisPin = 7; thisPin >= 1; thisPin--) {
    digitalWrite(thisPin, HIGH);  // On
    delay(timer);                 // Time buffer
    digitalWrite(thisPin, LOW);   // Off
  }
}