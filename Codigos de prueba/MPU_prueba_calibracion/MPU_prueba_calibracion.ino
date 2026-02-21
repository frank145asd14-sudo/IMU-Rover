// 2 resistencias de 10 KΩ (pull_up/conectadas a 3.3 V) para SCL y SDA

#include <MPU6050_light.h>
#include <Wire.h>

MPU6050 mpu(Wire);

float X_0 = 0, Y_0 = 0, suma_X_0 = 0, suma_Y_0 = 0;

void setup(){
  Serial.begin(115200);
  Wire.begin(37, 38);  // SDA, SCL
  mpu.begin();
  mpu.setFilterGyroCoef(0.75);      // Confianza en giroscopio (0.0-1.0)
  mpu.setFilterAccCoef(0.25);      // Confianza en acelerómetro
  delay(3000);        // Esperar ANTES para dejar quieto el sensor  
  mpu.calcOffsets();  // Luego calibra
  for(int i = 1; i<=10; i++){
    mpu.update();  // Primeras lectura después de calibrar
    suma_X_0 = suma_X_0 + mpu.getAngleX(); // Acumulacion de angulos iniciales
    suma_Y_0 = suma_Y_0 + mpu.getAngleY(); // Acumulacion de angulos iniciales
    delay(50);
  }
  X_0 = suma_X_0 / 10;  // Guardar ángulo inicial X
  Y_0 = suma_Y_0 / 10;  // Guardar ángulo inicial Y
}

void loop(){
  mpu.update();
  Serial.print("X: ");
  Serial.print(mpu.getAngleX() - X_0, 2);
  Serial.println("°");
  Serial.print("Y: ");
  Serial.print(mpu.getAngleY() - Y_0, 2);
  Serial.println("°");
  Serial.println(" ");
  delay(250);
}