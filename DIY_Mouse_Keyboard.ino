#include <Mouse.h>
#include <I2Cdev.h>
#include <MPU6050.h>
#include <Wire.h>
#include <Keyboard.h>

MPU6050 mpu;
// Creating variables
int16_t accx, accy; // Initial sensor reading variable
int prevX, prevY;   // Variable after filtering

const float filterValue = 0.95; // Filter for smoothing readings
const int mouseSpeed = 2;      // Mouse speed

int RightClickButton = 8;
int LeftClickButton = 9;
int ESCButton = 5;
int F5Button = 6;
int ForwardButton = 4;
int BackwardButton = 10;
int ModeButton = 7;

int Bluetooth_RX = 16;
int Bluetooth_TX = 14;

int Led = 1;

boolean buttonState = HIGH;
boolean lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

boolean buttonState_1 = HIGH;
boolean lastButtonState_1 = HIGH;
unsigned long lastDebounceTime_1 = 0;
unsigned long debounceDelay_1 = 50;

boolean buttonState_2 = HIGH;
boolean lastButtonState_2 = HIGH;
unsigned long lastDebounceTime_2 = 0;
unsigned long debounceDelay_2 = 50;

boolean buttonState_3 = HIGH;
boolean lastButtonState_3 = HIGH;
unsigned long lastDebounceTime_3 = 0;
unsigned long debounceDelay_3 = 50;

boolean buttonState_4 = HIGH;
boolean lastButtonState_4 = HIGH;
unsigned long lastDebounceTime_4 = 0;
unsigned long debounceDelay_4 = 50;

boolean buttonState_5 = HIGH;
boolean lastButtonState_5 = HIGH;
unsigned long lastDebounceTime_5 = 0;
unsigned long debounceDelay_5 = 50;

void setup() {
  Serial.begin(9600);
  Wire.begin();        // Start Wire communication
  mpu.initialize();    // Initialize MPU
  Mouse.begin();

  pinMode(Led, OUTPUT);
  pinMode(RightClickButton, INPUT_PULLUP);
  pinMode(LeftClickButton, INPUT_PULLUP);
  pinMode(ESCButton, INPUT_PULLUP);
  pinMode(F5Button, INPUT_PULLUP);
  pinMode(ForwardButton, INPUT_PULLUP);
  pinMode(BackwardButton, INPUT_PULLUP);
  pinMode(ModeButton, INPUT_PULLUP);
}

void loop() {
  // if (bluetooth.available() > 0) {
  //   // Mouse and keyboard commands will be executed only if Bluetooth device is paired
  //   mpu.getMotion6(&accx, &accy, NULL, NULL, NULL, NULL); // Read and store sensor x and y axes

  //   // Map variables to old variable and set mouse limits
  //   int deltaX = map(accx, -20000, 20000, -20, 20);
  //   int deltaY = map(accy, -20000, 20000, -20, 20);

  //   // Create final variable after calculations and filtering
  //   int newX = prevX + int(filterValue * (deltaX - prevX));
  //   int newY = prevY + int(filterValue * (deltaY - prevY));

  //   // Emulate mouse movement with filtered and calculated variables
  //   Mouse.move(mouseSpeed * newX, mouseSpeed * newY, 0);

  //   // Set final variable to be equal to the old one for new movements
  //   prevX = newX;
  //   prevY = newY;

  //   delay(10); // Wait for ms for sensor and mouse reading

  //   // Transmit commands via Bluetooth
  //   // HandleESCButton();
  //   // HandleF5Button();
  //   // HandleRightClickButton();
  //   // HandleLeftClickButton();
  //   // HandleForwardButton();
  //   // HandleBackwardButton();
  // }
  mpu.getMotion6(&accx, &accy, NULL, NULL, NULL, NULL); // Read and store sensor x and y axes

  // Map variables to old variable and set mouse limits
  int deltaX = map(accx, -20000, 20000, -20, 20);
  int deltaY = map(accy, -20000, 20000, -20, 20);

  // Create final variable after calculations and filtering
  int newX = prevX + int(filterValue * (deltaX - prevX));
  int newY = prevY + int(filterValue * (deltaY - prevY));

  // Emulate mouse movement with filtered and calculated variables
  Mouse.move(mouseSpeed * newX, mouseSpeed * newY, 0);

  // Set final variable to be equal to the old one for new movements
  prevX = newX;
  prevY = newY;

  delay(10); // Wait for ms for sensor and mouse reading
  
  HandleESCButton();
  HandleF5Button();
  HandleRightClickButton();
  HandleLeftClickButton();
  HandleForwardButton();
  HandleBackwardButton();
}
void HandleESCButton() {
  boolean reading = digitalRead(ESCButton);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        Serial.println("ESC Button Pressed");
        Keyboard.press(KEY_ESC);
        delay(50);
        Keyboard.release(KEY_ESC);
      }
    }
  }
  lastButtonState = reading;
}
void HandleF5Button() {
  boolean reading_1 = digitalRead(F5Button);

  if (reading_1 != lastButtonState_1) {
    lastDebounceTime_1 = millis();
  }

  if ((millis() - lastDebounceTime_1) > debounceDelay_1) {
    if (reading_1 != buttonState_1) {
      buttonState_1 = reading_1;
      if (buttonState_1 == LOW) {
        Serial.println("F5 Button Pressed");
        Keyboard.press(KEY_F5);
        delay(50);
        Keyboard.release(KEY_F5);
      }
    }
  }
  lastButtonState_1 = reading_1;
}
void HandleRightClickButton() {
  boolean reading_2 = digitalRead(RightClickButton);

  if (reading_2 != lastButtonState_2) {
    lastDebounceTime_2 = millis();
  }

  if ((millis() - lastDebounceTime_2) > debounceDelay_2) {
    if (reading_2 != buttonState_2) {
      buttonState_2 = reading_2;
      if (buttonState_2 == LOW) {
        Serial.println("RightClickButton Button Pressed");
        Mouse.click(MOUSE_RIGHT);
        delay(50);
      }
    }
  }
  lastButtonState_2 = reading_2;
}
void HandleLeftClickButton() {
  boolean reading_3 = digitalRead(LeftClickButton);

  if (reading_3 != lastButtonState_3) {
    lastDebounceTime_3 = millis();
  }

  if ((millis() - lastDebounceTime_3) > debounceDelay_3) {
    if (reading_3 != buttonState_3) {
      buttonState_3 = reading_3;
      if (buttonState_3 == LOW) {
        Serial.println("LeftClickButton Button Pressed");
        Mouse.click(MOUSE_LEFT);
        delay(50);
      }
    }
  }
  lastButtonState_3 = reading_3;
}
void HandleForwardButton() {
  boolean reading_4 = digitalRead(ForwardButton);

  if (reading_4 != lastButtonState_4) {
    lastDebounceTime_4 = millis();
  }

  if ((millis() - lastDebounceTime_4) > debounceDelay_4) {
    if (reading_4 != buttonState_4) {
      buttonState_4 = reading_4;
      if (buttonState_4 == LOW) {
        Serial.println("ForwardButton Button Pressed");
        Keyboard.press(KEY_RIGHT_ARROW);
        delay(50);
        Keyboard.release(KEY_RIGHT_ARROW);
      }
    }
  }
  lastButtonState_4 = reading_4;
}
void HandleBackwardButton() {
  boolean reading_5 = digitalRead(BackwardButton);

  if (reading_5 != lastButtonState_5) {
    lastDebounceTime_5 = millis();
  }

  if ((millis() - lastDebounceTime_5) > debounceDelay_5) {
    if (reading_5 != buttonState_5) {
      buttonState_5 = reading_5;
      if (buttonState_5 == LOW) {
        Serial.println("BackwardButton Button Pressed");
        Keyboard.press(KEY_LEFT_ARROW);
        delay(50);
        Keyboard.release(KEY_LEFT_ARROW);
      }
    }
  }
  lastButtonState_5 = reading_5;
}