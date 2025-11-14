int pinR = 9;
int pinG = 10;
int pinB = 11;

void setColor(int r, int g, int b) {
  analogWrite(pinR, r);
  analogWrite(pinG, g);
  analogWrite(pinB, b);
}

void setup() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);

  // roxo como exemplo
  setColor(255, 0, 150);
}

void loop() {}
