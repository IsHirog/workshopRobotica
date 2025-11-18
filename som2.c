const int PINO_SENSOR = A0;

const int LED_VERDE = 6;
const int LED_AMARELO = 7;
const int LED_VERMELHO = 8;

// Média móvel
const int N = 10;
int buffer[N];
int indexBuffer = 0;
long soma = 0;

// Thresholds com histerese (EM PORCENTAGEM)
int limiarVerde_ON = 10;
int limiarVerde_OFF = 7;

int limiarAmarelo_ON = 35;
int limiarAmarelo_OFF = 30;

int limiarVermelho_ON = 70;
int limiarVermelho_OFF = 65;

// Estado dos LEDs
bool verdeLigado = false;
bool amareloLigado = false;
bool vermelhoLigado = false;

// Ruído ambiente (calibrado no início)
int nivelAmbiente = 0;

void setup() {
  Serial.begin(9600);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Inicializa buffer
  for (int i = 0; i < N; i++) buffer[i] = 0;

  // --- Calibração automática ---
  long somaCalib = 0;
  int leituras = 200;

  Serial.println("Calibrando nivel ambiente...");

  for (int i = 0; i < leituras; i++) {
    somaCalib += analogRead(PINO_SENSOR);
    delay(5);
  }

  nivelAmbiente = somaCalib / leituras;

  Serial.print("Nivel ambiente calibrado: ");
  Serial.println(nivelAmbiente);
}

void loop() {

  int leitura = analogRead(PINO_SENSOR);

  // --- Média móvel ---
  soma -= buffer[indexBuffer];
  buffer[indexBuffer] = leitura;
  soma += buffer[indexBuffer];
  indexBuffer = (indexBuffer + 1) % N;

  int valorSuave = soma / N;

  // Compensação do ambiente
  int valorCompensado = valorSuave - nivelAmbiente;
  if (valorCompensado < 0) valorCompensado = 0;
  if (valorCompensado > 600) valorCompensado = 600; // limite superior

  // Converte para porcentagem 0–100
  int porcentagem = map(valorCompensado, 0, 600, 0, 100);
  if (porcentagem > 100) porcentagem = 100;

  // --- Barra gráfica ---
  int barras = porcentagem / 10;
  String grafico = "[";
  for (int i = 0; i < 10; i++) {
    if (i < barras) grafico += "#";
    else grafico += "-";
  }
  grafico += "]";

  Serial.print(grafico);
  Serial.print(" ");
  Serial.print(porcentagem);
  Serial.println("%");

  // --- LED Verde ---
  if (!verdeLigado && porcentagem >= limiarVerde_ON) verdeLigado = true;
  if (verdeLigado && porcentagem < limiarVerde_OFF) verdeLigado = false;

  // --- LED Amarelo ---
  if (!amareloLigado && porcentagem >= limiarAmarelo_ON) amareloLigado = true;
  if (amareloLigado && porcentagem < limiarAmarelo_OFF) amareloLigado = false;

  // --- LED Vermelho ---
  if (!vermelhoLigado && porcentagem >= limiarVermelho_ON) vermelhoLigado = true;
  if (vermelhoLigado && porcentagem < limiarVermelho_OFF) vermelhoLigado = false;

  // Saída
  digitalWrite(LED_VERDE, verdeLigado ? HIGH : LOW);
  digitalWrite(LED_AMARELO, amareloLigado ? HIGH : LOW);
  digitalWrite(LED_VERMELHO, vermelhoLigado ? HIGH : LOW);

  delay(30);
}
