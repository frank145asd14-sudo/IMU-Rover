#include <SoftwareSerial.h>

// HC-05 en pines 5 (RX) y 6 (TX)
SoftwareSerial BT(6, 5);  // RX, TX

void setup() {
  // Monitor Serial (USB)
  Serial.begin(9600);
  
  // HC-05 - Usa 38400 para comandos AT
  BT.begin(38400);
  
  delay(1000);
  Serial.println("\nArduino Nano + HC-05 Maestro");
  Serial.println("Escribe comandos AT manualmente:");
}

void loop() {
  // 1. Enviar comandos AT desde Serial Monitor a HC-05
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    
    Serial.print(">>> ");
    Serial.println(comando);
    BT.println(comando);
  }
  
  // 2. Mostrar respuestas del HC-05
  if (BT.available()) {
    String respuesta = BT.readString();
    respuesta.trim();
    
    if (respuesta.length() > 0) {
      Serial.print("HC-05: ");
      Serial.println(respuesta);
    }
  }
  
  delay(10);
}