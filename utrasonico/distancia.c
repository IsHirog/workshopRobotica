#include <Ultrasonic.h> 

#define pino_trigger 4  
#define pino_echo 5  
// Taxa de comunicação serial
#define BAUD_RATE 9600

Ultrasonic ultrasonic(pino_trigger, pino_echo);  

void setup() {  
  // Inicializa a comunicação serial
  Serial.begin(BAUD_RATE); 
  Serial.println("Monitoramento de Distancia - Sensor Ultrassonico");
  Serial.println("----------------------------------------------");
}  

void loop() {  
  float cmMsec, inMsec;  
  
  // 1. Faz a leitura do tempo do ultrassom
  long microsec = ultrasonic.timing();  
  
  // 2. Converte o tempo para distancia em CM e Polegadas
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);  
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);  

  // 3. Exibe os dados no Monitor Serial
  Serial.print("Distancia: "); 
  Serial.print(cmMsec);        
  Serial.print(" cm");         
  Serial.print(" | ");
  Serial.print(inMsec);        
  Serial.println(" in");       // Pula uma linha no final para a próxima leitura

  delay(1000); // Aguarda 1 segundo antes da próxima leitura (ajustado de 2000ms para 1000ms para um feedback mais rápido)
}