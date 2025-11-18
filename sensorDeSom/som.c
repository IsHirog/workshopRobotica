const int PINO_SENSOR = A0;

const int LED_VERDE = 6;
const int LED_AMARELO = 7;
const int LED_VERMELHO = 8;

void setup() {
  Serial.begin(9600);

  pinMode(PINO_SENSOR, INPUT);

  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

void loop() {

  int valor = analogRead(PINO_SENSOR);
  Serial.println(valor);
  delay(50);

  // thresholds — ajuste conforme seu sensor
  int nivelVerde = 300;
  int nivelAmarelo = 600;
  int nivelVermelho = 800;

  // Verde liga sempre que passar do primeiro nível
  if (valor >= nivelVerde) {
    digitalWrite(LED_VERDE, HIGH);
  } else {
    digitalWrite(LED_VERDE, LOW);
  }

  // Amarelo adiciona ao Verde
  if (valor >= nivelAmarelo) {
    digitalWrite(LED_AMARELO, HIGH);
  } else {
    digitalWrite(LED_AMARELO, LOW);
  }

  // Vermelho adiciona aos dois anteriores
  if (valor >= nivelVermelho) {
    digitalWrite(LED_VERMELHO, HIGH);
  } else {
    digitalWrite(LED_VERMELHO, LOW);
  }
}
