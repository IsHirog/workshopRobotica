// ---------------- CONFIG ----------------
const int PINO_SENSOR = A0;

const int LED_VERDE = 6;
const int LED_AMARELO = 7;
const int LED_VERMELHO = 8;

// Média móvel
const int N = 10;
int buffer[N];
int indexBuffer = 0;
long soma = 0;

// Thresholds de porcentagem
int limiarVerde_ON = 3;
int limiarVerde_OFF = 1;

int limiarAmarelo_ON = 10;
int limiarAmarelo_OFF = 7;

int limiarVermelho_ON = 20;
int limiarVermelho_OFF = 11;

// Estados
bool verdeLigado = false;
bool amareloLigado = false;
bool vermelhoLigado = false;

// Nível ambiente calibrado
int nivelAmbiente = 0;


// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  // Garante que o Serial Monitor abra antes de iniciar
  while (!Serial) {}

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  for (int i = 0; i < N; i++) buffer[i] = 0;

  // -------- Calibração do ambiente --------
  long somaCalib = 0;
  int leituras = 200;

  Serial.println("Calibrando nivel ambiente... Fique em silencio por 1 segundo.");

  for (int i = 0; i < leituras; i++) {
    somaCalib += analogRead(PINO_SENSOR);
    delay(5);
  }

  nivelAmbiente = somaCalib / leituras;

  Serial.print("Nível ambiente calibrado: ");
  Serial.println(nivelAmbiente);
  Serial.println("-------------------------------------");
}


// ---------------- LOOP ----------------
void loop() {

  int leitura = analogRead(PINO_SENSOR);

  // --- Média Móvel ---
  soma -= buffer[indexBuffer];
  buffer[indexBuffer] = leitura;
  soma += buffer[indexBuffer];
  indexBuffer = (indexBuffer + 1) % N;

  int valorSuave = soma / N;

  // --- Compensação do ruído ambiente ---
  int valorCompensado = valorSuave - nivelAmbiente;
  if (valorCompensado < 0) valorCompensado = 0;
  if (valorCompensado > 600) valorCompensado = 600;

  // --- Converte para % ---
  int porcentagem = map(valorCompensado, 0, 600, 0, 100);
  if (porcentagem > 100) porcentagem = 100;

  // --- Barra gráfica estilo VU ---
  int barras = porcentagem / 10;
  String grafico = "[";
  for (int i = 0; i < 10; i++) {
    grafico += (i < barras) ? "#" : "-";
  }
  grafico += "]";

  Serial.print(grafico);
  Serial.print("  ");
  Serial.print(porcentagem);
  Serial.println("%");


  // --------- LÓGICA COM HISTERSE ---------
  // Verde
  if (!verdeLigado && porcentagem >= limiarVerde_ON) verdeLigado = true;
  if (verdeLigado && porcentagem < limiarVerde_OFF) verdeLigado = false;

  // Amarelo
  if (!amareloLigado && porcentagem >= limiarAmarelo_ON) amareloLigado = true;
  if (amareloLigado && porcentagem < limiarAmarelo_OFF) amareloLigado = false;

  // Vermelho
  if (!vermelhoLigado && porcentagem >= limiarVermelho_ON) vermelhoLigado = true;
  if (vermelhoLigado && porcentagem < limiarVermelho_OFF) vermelhoLigado = false;

  // Saída acumulativa (verde → amarelo → vermelho)
  digitalWrite(LED_VERDE,   verdeLigado ? HIGH : LOW);
  digitalWrite(LED_AMARELO, amareloLigado ? HIGH : LOW);
  digitalWrite(LED_VERMELHO,vermelhoLigado ? HIGH : LOW);

  delay(30);
}
