#include <HardwareSerial.h>

HardwareSerial SerialBT(2);
#define RX_PIN 47
#define TX_PIN 48

void setup() {
  Serial.begin(115200);
  SerialBT.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  
  delay(1000);
  Serial.println("✅ HC-05 CONECTADO");
  Serial.println("Escribe mensajes para enviar al esclavo");
  Serial.println("Verás respuestas automáticamente");
}

void loop() {
  // 1. ENVIAR al esclavo
  if (Serial.available()) {
    String mensaje = Serial.readStringUntil('\n');
    mensaje.trim();
    
    Serial.print("📤 Enviando: ");
    Serial.println(mensaje);
    SerialBT.println(mensaje);
  }
  
  // 2. RECIBIR del esclavo
  if (SerialBT.available()) {
    String respuesta = SerialBT.readString();
    respuesta.trim();
    
    if (respuesta.length() > 0) {
      Serial.print("📥 Recibido: ");
      Serial.println(respuesta);
    }
  }
  
  delay(10);
}