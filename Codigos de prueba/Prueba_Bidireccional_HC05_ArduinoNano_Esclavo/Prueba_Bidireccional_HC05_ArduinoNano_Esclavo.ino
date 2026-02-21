#include <SoftwareSerial.h>
SoftwareSerial BT(6, 5);  // RX=5, TX=6

void setup() {
  Serial.begin(9600);
  BT.begin(115200);
  
  Serial.println("✅ Esclavo conectado y listo");
  Serial.println("Mensajes recibidos aparecerán aquí");
}

void loop() {
  // 1. RECIBIR del maestro
  if (BT.available()) {
    String mensaje = BT.readString();
    mensaje.trim();
    
    Serial.print("📥 Maestro dice: ");
    Serial.println(mensaje);
    
    // Responder automáticamente
    BT.print("Recibido: ");
    BT.println(mensaje);
    Serial.println("✓ Respuesta enviada");
  }
  
  // 2. ENVIAR al maestro (opcional)
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    
    if (input.length() > 0) {
      BT.println(input);
      Serial.print("📤 Enviado: ");
      Serial.println(input);
    }
  }
  
  delay(10);
}