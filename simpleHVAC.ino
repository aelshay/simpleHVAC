// Arduino HVAC Project with LCD Menu and Fan Control
#include <DHT.h>
#include <Servo.h>
#include <LiquidCrystal.h>

// --- Pins ---
#define DHTPIN 2
#define DHTTYPE DHT11
#define SERVOPIN 3
#define BUTTON_LEFT 4
#define BUTTON_RIGHT 5
#define FANPIN 13
#define POTPIN A0

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);
DHT dht(DHTPIN, DHTTYPE);
Servo myServo;

// --- Global Variables ---
float temperature = 0;
float humidity = 0;
float setpoint = 25.0;
int fanLevel = 1;  // 0 = Low, 1 = Mid, 2 = High
bool fanMotion = false;
bool acEnabled = true;
int menuIndex = 0;
unsigned long lastMotionTime = 0;
bool sweepRight = true;

// --- Setup ---
void setup() {
  pinMode(FANPIN, OUTPUT);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  myServo.attach(SERVOPIN);
  dht.begin();
  lcd.begin(16, 2);
  lcd.print("Starting...");
  delay(1000);
  lcd.clear();
}

// --- Menu Labels ---
const char* menuItems[] = {
  "Temp/Humidity",
  "Set Temp", 
  "Fan Motion", 
  "AC Control", 
  "Fan Power"
};
const int menuSize = sizeof(menuItems) / sizeof(menuItems[0]);

// --- Loop ---
void loop() {
  readSensors();
  handleMenu();
  controlFan();
  controlServo();
  delay(200);
}

void readSensors() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
}

void handleMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(menuItems[menuIndex]);

  if (menuIndex == 0) {  // Temp/Humidity
    lcd.setCursor(0, 1);
    lcd.print("T:"); lcd.print(temperature); lcd.print("C");
    lcd.print(" H:"); lcd.print(humidity);

  } else if (menuIndex == 1) {  // Set Temp
    int pot = analogRead(POTPIN);
    setpoint = map(pot, 0, 1023, 15, 35);
    lcd.setCursor(0, 1);
    lcd.print("Set: "); lcd.print(setpoint); lcd.print("C");

  } else if (menuIndex == 2) {  // Fan Motion
    int pot = analogRead(POTPIN);
    fanMotion = pot > 512;
    lcd.setCursor(0, 1);
    lcd.print("Motion: "); lcd.print(fanMotion ? "On " : "Off");

  } else if (menuIndex == 3) {  // AC Control
    int pot = analogRead(POTPIN);
    acEnabled = pot > 512;
    lcd.setCursor(0, 1);
    lcd.print("AC: "); lcd.print(acEnabled ? "On " : "Off");

  } else if (menuIndex == 4) {  // Fan Power
    int pot = analogRead(POTPIN);
    fanLevel = map(pot, 0, 1023, 0, 2);
    lcd.setCursor(0, 1);
    lcd.print("Power: ");
    lcd.print(fanLevel == 0 ? "Low " : fanLevel == 1 ? "Mid " : "High");
  }

  // Handle buttons
  if (digitalRead(BUTTON_LEFT) == LOW) {
    menuIndex = (menuIndex - 1 + menuSize) % menuSize;
    delay(200);
  } else if (digitalRead(BUTTON_RIGHT) == LOW) {
    menuIndex = (menuIndex + 1) % menuSize;
    delay(200);
  }
}

void controlFan() {
  if (acEnabled && temperature > setpoint) {
    // Adjust fan speed using PWM levels
    int pwm = fanLevel == 0 ? 85 : fanLevel == 1 ? 170 : 255;
    analogWrite(FANPIN, pwm);
  } else {
    analogWrite(FANPIN, 0);
  }
}

void controlServo() {
  if (fanMotion) {
    unsigned long now = millis();
    if (now - lastMotionTime > 50) {
      static int angle = 75;
      angle += sweepRight ? 1 : -1;
      if (angle >= 135) sweepRight = false;
      if (angle <= 15) sweepRight = true;
      myServo.write(angle);
      lastMotionTime = now;
    }
  } else {
    myServo.write(75);  // default position
  }
}