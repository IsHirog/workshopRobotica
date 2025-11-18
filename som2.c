const int PINO_SENSOR = A0;

const int LED_VERDE = 6;
const int LED_AMARELO = 7;
const int LED_VERMELHO = 8;

// Média móvel
const int N = 10;
int buffer[N];
int indexBuffer = 0;
long soma = 0;

// Thresholds com histerese
int limiarVerde_ON = 300;
int limiarVerde_OFF = 250;

int limiarAmarelo_ON = 600;
int limiarAmarelo_OFF = 550;

int limiarVermelho_ON = 800;
int limiarVermelho_OFF = 750;

// Estado atual dos LEDs
bool verdeLigado = false;
bool amareloLigado = false;
bool vermelhoLigado = false;

void setup() {
  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  for (int i = 0; i < N; i++) {
    buffer[i] = 0;
  }
}

void loop() {

  int leitura = analogRead(PINO_SENSOR);

  // --- Média móvel ---
  soma -= buffer[indexBuffer];
  buffer[indexBuffer] = leitura;
  soma += buffer[indexBuffer];
  indexBuffer = (indexBuffer + 1) % N;

  int valorSuave = soma / N;

  Serial.println(valorSuave);
  delay(20);

  // --- LED Verde ---
  if (!verdeLigado && valorSuave >= limiarVerde_ON) {
    verdeLigado = true;
  }
  if (verdeLigado && valorSuave < limiarVerde_OFF) {
    verdeLigado = false;
  }

  // --- LED Amarelo ---
  if (!amareloLigado && valorSuave >= limiarAmarelo_ON) {
    amareloLigado = true;
  }
  if (amareloLigado && valorSuave < limiarAmarelo_OFF) {
    amareloLigado = false;
  }

  // --- LED Vermelho ---
  if (!vermelhoLigado && valorSuave >= limiarVermelho_ON) {
    vermelhoLigado = true;
  }
  if (vermelhoLigado && valorSuave < limiarVermelho_OFF) {
    vermelhoLigado = false;
  }

  // Saída final (acumulativa)
  digitalWrite(LED_VERDE,   verdeLigado ? HIGH : LOW);
  digitalWrite(LED_AMARELO, amareloLigado ? HIGH : LOW);
  digitalWrite(LED_VERMELHO,vermelhoLigado ? HIGH : LOW);
}
