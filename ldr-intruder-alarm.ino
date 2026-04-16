const int ldrPin      = A0;
const int buzzerPin   = 8;
const int redPin      = 7;
const int greenPin    = 5;
const int bluePin     = 6;

int baselineLight = 0;
bool alarmActive  = false;

int melody[] = {
  659, 623, 659, 623, 659, 494, 587, 523, 440,
  262, 330, 440, 494,
  330, 415, 494, 523,
  330, 659, 623, 659, 623, 659, 494, 587, 523, 440,
  262, 330, 440, 494,
  330, 523, 494, 440
};

int duration[] = {
  150, 150, 150, 150, 150, 150, 150, 150, 300,
  150, 150, 150, 300,
  150, 150, 150, 300,
  150, 150, 150, 150, 150, 150, 150, 150, 150, 300,
  150, 150, 150, 300,
  150, 150, 150, 400
};

int noteCount = sizeof(melody) / sizeof(melody[0]);

void setColor(int r, int g, int b) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}

void playFurElise() {
  for (int i = 0; i < noteCount; i++) {
    tone(buzzerPin, melody[i], duration[i]);
    delay(duration[i] + 30);
  }
  noTone(buzzerPin);
  alarmActive = false;
}

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Calibrate baseline over 1 second
  long sum = 0;
  for (int i = 0; i < 20; i++) {
    sum += analogRead(ldrPin);
    delay(50);
  }
  baselineLight = sum / 20;

  // Blink green twice to confirm calibration done
  for (int i = 0; i < 2; i++) {
    setColor(0, 255, 0);
    delay(200);
    setColor(0, 0, 0);
    delay(200);
  }

  // Start in safe state — green
  setColor(0, 255, 0);
}

void loop() {
  int lightVal = analogRead(ldrPin);

  if (lightVal < baselineLight - 200) {
    if (!alarmActive) {
      alarmActive = true;
      setColor(255, 0, 0);  // red — alarm
      playFurElise();
    }
  } else {
    alarmActive = false;
    setColor(0, 255, 0);    // green — safe
    noTone(buzzerPin);
  }
}
