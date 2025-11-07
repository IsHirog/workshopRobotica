// --- Configuração dos pinos ---
const int PINO_SENSOR = 3;  // Sensor com pino único (trigger + echo no mesmo fio)

// --- Parâmetros ---
const unsigned long TIMEOUT = 30000UL; // tempo limite em microssegundos (~5m de alcance)

// --- Setup ---
void setup() {
  Serial.begin(9600);
  pinMode(PINO_SENSOR, OUTPUT);
  digitalWrite(PINO_SENSOR, LOW);
  delay(100);
}

// --- Loop principal ---
void loop() {
  float distancia = medirDistancia(PINO_SENSOR);

  if (distancia >= 0) {
    Serial.print("Distancia: ");
    Serial.print(distancia, 2);
    Serial.println(" cm");
  } else {
    Serial.println("Sem leitura (fora de alcance)");
  }

  delay(200);
}

// --- Função de medição ---
float medirDistancia(int pino) {
  // Envia pulso de trigger
  pinMode(pino, OUTPUT);
  digitalWrite(pino, LOW);
  delayMicroseconds(2);
  digitalWrite(pino, HIGH);
  delayMicroseconds(10);
  digitalWrite(pino, LOW);

  // Muda para modo leitura (echo)
  pinMode(pino, INPUT);
  unsigned long duracao = pulseIn(pino, HIGH, TIMEOUT);

  if (duracao == 0) return -1;  // caso não receba eco

  // Calcula distância (cm): tempo (µs) / 58 = cm
  return duracao / 58.0;
}
