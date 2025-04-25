const int pinoLDR = A0; // pino onde o LDR está conectado
const int pinoLED = 7;  // pino onde o LED está conectado
int leitura = 0;        // variável para armazenar o valor lido pelo ADC

void setup() {
  pinMode(pinoLDR, INPUT); 
  pinMode(pinoLED, OUTPUT);

  Serial.begin(9600); // inicia a comunicação serial
}

void loop() {
  leitura = analogRead(pinoLDR); // lê o valor do LDR

  Serial.print("Valor do LDR: ");
  Serial.println(leitura); // mostra o valor no monitor serial

  if(leitura < 40) {
    digitalWrite(pinoLED, HIGH); // acende o LED
  }
  else {
    digitalWrite(pinoLED, LOW);  // apaga o LED
  }

  delay(100); // espera 100ms para nova leitura
}
