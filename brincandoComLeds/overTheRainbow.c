int pinR = 9;
int pinG = 10;
int pinB = 11;

// Converte HSV para RGB (0-360, 0-1, 0-1)
void hsvToRgb(float h, float s, float v, int &r, int &g, int &b) {
  float c = v * s;
  float x = c * (1 - abs(fmod(h / 60.0, 2) - 1));
  float m = v - c;

  float r1, g1, b1;

  if (h < 60)      { r1 = c; g1 = x; b1 = 0; }
  else if (h < 120){ r1 = x; g1 = c; b1 = 0; }
  else if (h < 180){ r1 = 0; g1 = c; b1 = x; }
  else if (h < 240){ r1 = 0; g1 = x; b1 = c; }
  else if (h < 300){ r1 = x; g1 = 0; b1 = c; }
  else            { r1 = c; g1 = 0; b1 = x; }

  r = (r1 + m) * 255;
  g = (g1 + m) * 255;
  b = (b1 + m) * 255;
}

void setup() {
  pinMode(pinR, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(pinB, OUTPUT);
}

void loop() {
  for (int hue = 0; hue < 360; hue++) {
    int r, g, b;
    hsvToRgb(hue, 1.0, 1.0, r, g, b);  // saturação máxima, brilho máximo

    analogWrite(pinR, r);
    analogWrite(pinG, g);
    analogWrite(pinB, b);

    delay(10);  // Velocidade do arco-íris
  }
}
