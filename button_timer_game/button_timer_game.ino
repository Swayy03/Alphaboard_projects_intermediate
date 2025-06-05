const int button1Pin = A4;
const int button2Pin = A5;
const int ledPin = 11;
const int buzzerPin = 9;

bool gameStarted = false;
unsigned long startTime = 0;

void setup() {
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);

  randomSeed(analogRead(A1)); // use noise from potentiometer as seed
}

void loop() {
  if (!gameStarted) {
    delay(random(2000, 5000));  // Wait randomly 2–5 sec
    digitalWrite(ledPin, HIGH); // Start signal
    startTime = millis();
    gameStarted = true;
  }

  if (gameStarted) {
    if (digitalRead(button1Pin) == LOW) {
      gameWon(1);
    } else if (digitalRead(button2Pin) == LOW) {
      gameWon(2);
    }
  }
}

void gameWon(int player) {
  digitalWrite(ledPin, LOW);
  tone(buzzerPin, 1000, 300); // 1kHz beep
  Serial.print("Player ");
  Serial.print(player);
  Serial.println(" wins!");
  delay(2000);
  gameStarted = false;
}

