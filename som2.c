const int PINO_SENSOR = A0;

const int LED_VERDE = 6;
const int LED_AMARELO = 7;
const int LED_VERMELHO = 8;

// Média móvel mais sensível e suave
const int N = 15;
int buffer[N];
int indexBuffer = 0;
long soma = 0;

// Thresholds mais sensíveis
int limiarVerde_ON = 150;
int limiarVerde_OFF = 120;

int limiarAmarelo_ON = 350;
int limiarAmarelo_OFF = 300;

int limiarVermelho_ON = 550;
int limiarVermelho_OFF = 500;

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

  // Percentual (0–100)
  int porcento = map(valorSuave, 0, 1023, 0, 100);

  // Quantos blocos vão acender (de 0 a 10)
  int blocos = map(valorSuave, 0, 1023, 0, 10);

  // Gera a barra
  String barra = "[";
  for (int i = 0; i < 10; i++) {
    if (i < blocos) barra += "#";
    else barra += "-";
  }
  barra += "]";

  // PRINT no Serial Monitor
  Serial.print(barra);
  Serial.print("  ");
  Serial.print(porcento);
  Serial.println("%");

  delay(20);

  // --- LED Verde ---
  if (!verdeLigado && valorSuave >= limiarVerde_ON) verdeLigado = true;
  if (verdeLigado && valorSuave < limiarVerde_OFF) verdeLigado = false;

  // --- LED Amarelo ---
  if (!amareloLigado && valorSuave >= limiarAmarelo_ON) amareloLigado = true;
  if (amareloLigado && valorSuave < limiarAmarelo_OFF) amareloLigado = false;

  // --- LED Vermelho ---
  if (!vermelhoLigado && valorSuave >= limiarVermelho_ON) vermelhoLigado = true;
  if (vermelhoLigado && valorSuave < limiarVermelho_OFF) vermelhoLigado = false;

  // Saída final
  digitalWrite(LED_VERDE,   verdeLigado ? HIGH : LOW);
  digitalWrite(LED_AMARELO, amareloLigado ? HIGH : LOW);
  digitalWrite(LED_VERMELHO,vermelhoLigado ? HIGH : LOW);
}
