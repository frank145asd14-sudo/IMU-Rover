#include <HardwareSerial.h>

// Usar Serial2 para HC-05
HardwareSerial SerialBT(2);
#define RX_PIN 47   // HC-05 TX → ESP32 RX (47)
#define TX_PIN 48   // HC-05 RX → ESP32 TX (48)

void setup() {
  // Monitor Serial (USB)
  Serial.begin(115200);
  
  // HC-05 - Usa 38400 para comandos AT
  SerialBT.begin(38400, SERIAL_8N1, RX_PIN, TX_PIN);
  
  delay(1000);
  Serial.println("\nHC-05 Maestro - Listo");
  Serial.println("Escribe comandos AT manualmente:");
  Serial.println("Ejemplo: AT+ROLE=1");
}

void loop() {
  // 1. Enviar comandos AT desde Monitor Serial a HC-05
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();
    
    Serial.print(">>> ");
    Serial.println(comando);
    SerialBT.println(comando);
  }
  
  // 2. Mostrar respuestas del HC-05
  if (SerialBT.available()) {
    String respuesta = SerialBT.readString();
    respuesta.trim();
    
    if (respuesta.length() > 0) {
      Serial.print("HC-05: ");
      Serial.println(respuesta);
    }
  }
  
  delay(10);
}