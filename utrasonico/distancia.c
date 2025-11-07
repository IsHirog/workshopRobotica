/******************************************************
 * Medindo Distância com HC-SR04
 ******************************************************/

const int TRIG = 3;
const int ECHO = 2;
const int distancia_obstaculo = 20;

void setup() {
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.println("Iniciando sensor ultrassônico...");
}

void loop() {
  long distancia = medirDistancia();

  if (distancia == 0) {
    Serial.println("Falha na leitura (sem eco)");
  } else if (distancia <= distancia_obstaculo) {
    Serial.print("Com obstáculo: ");
    Serial.print(distancia);
    Serial.println(" cm");
  } else {
    Serial.print("Sem obstáculo: ");
    Serial.print(distancia);
    Serial.println(" cm");
  }

  delay(300);
}

long medirDistancia() {
  // Garante que o TRIG começa em LOW
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);

  // Envia pulso de 10 µs
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Mede duração do pulso no ECHO
  long duracao = pulseIn(ECHO, HIGH, 30000); // timeout de 30 ms

  // Se não recebeu eco, retorna 0
  if (duracao == 0) return 0;

  // Converte tempo em distância (cm)
  long distancia = duracao / 58.2;
  return distancia;
}
