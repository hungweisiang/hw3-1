int R = 3;
int G = 5;
int B = 6;
int button = 2;

int mode = 0;
int buttonState = LOW;
int lastReading = LOW;

unsigned long lastDebounceTime = 0;
unsigned long lastBlinkTime = 0;

bool lightOn = true;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(button, INPUT);

  setColor(0);
}

void setColor(int color) {
  if (color == 0) {
    // 白色
    digitalWrite(R, LOW);
    digitalWrite(G, LOW);
    digitalWrite(B, LOW);
  }
  else if (color == 1) {
    // 紅色
    digitalWrite(R, LOW);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
  else if (color == 2) {
    // 綠色
    digitalWrite(R, HIGH);
    digitalWrite(G, LOW);
    digitalWrite(B, HIGH);
  }
  else if (color == 3) {
    // 藍色
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, LOW);
  }
}

void loop() {
  int reading = digitalRead(button);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if (millis() - lastDebounceTime > 50) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        mode = (mode + 1) % 4;
        lastBlinkTime = millis();
        lightOn = true;
      }
    }
  }

  lastReading = reading;

  if (mode == 0) {
    lightOn = true;
  }
  else {
    int speed;

    if (mode == 1) {
      speed = 1000;
    }
    else if (mode == 2) {
      speed = 500;
    }
    else {
      speed = 200;
    }

    if (millis() - lastBlinkTime >= speed) {
      lastBlinkTime = millis();
      lightOn = !lightOn;
    }
  }

  if (lightOn) {
    setColor(mode);
  }
  else {
    digitalWrite(R, HIGH);
    digitalWrite(G, HIGH);
    digitalWrite(B, HIGH);
  }
}