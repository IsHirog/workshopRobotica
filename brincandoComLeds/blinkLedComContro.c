void setup() {
  pinMode(/*defina aqui qual a porta esta o led*/ 8 , OUTPUT); // Define o pino 8 como saída
}

void loop() {
  digitalWrite(8, HIGH); // Liga o LED no pino 8
  delay(1000);           // Espera 1 segundo
  digitalWrite(8, LOW);  // Desliga o LED
  delay(1000);           // Espera 1 segundo
}
