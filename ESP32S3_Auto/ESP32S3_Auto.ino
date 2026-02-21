#include <HardwareSerial.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include <Adafruit_NeoPixel.h>

#define pinRGB 48
#define RX_PIN 36
#define TX_PIN 35
#define STA_TE_PIN 47
#define SDA_PIN 37
#define SCL_PIN 38
#define Tiempo_Reenvio 200  // Tiempo para reenviar el comando en loops

HardwareSerial hc05(1);
MPU6050 mpu(Wire);
Adafruit_NeoPixel neo_RGB(1, pinRGB, NEO_GRB + NEO_KHZ800);

float X_0 = 0, Y_0 = 0, suma_X_0 = 0, suma_Y_0 = 0;  // Variables de la calibracion del MPU
int comando = 0, last_comando = 1;  // Variables para enviar al auto
int t = 0;  // Variable del contador para reenviar el comando
int fuera_rango = 0;  // Variable para evitar angulos grandes
float X, Y; // Angulos de inclinacion

void verificador_HC05();
void calibracion_MPU();
void determinar_comando();
void enviar_comando_diferente();
void reenviar_comando();
void verificar_dentro_rango();
void RGB(int R, int G, int B);

void setup(){
  Serial.begin(115200);
  hc05.begin(115200, SERIAL_8N1, RX_PIN, TX_PIN);
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.begin();
  pinMode(STA_TE_PIN, INPUT);
  neo_RGB.begin();
  neo_RGB.setBrightness(10);
  RGB(0, 0, 255);  // Azul
  verificador_HC05();
  RGB(0, 150, 255);  // Celeste
  calibracion_MPU();
  RGB(0, 255, 0);  // Verde
}

void loop(){
  mpu.update();  // Actualiza los datos del MPU
  X = mpu.getAngleX() - X_0;  // Angulo X
  Y = mpu.getAngleY() - Y_0;  // Angulo Y
  verificar_dentro_rango();
  if(fuera_rango == 0){
    if(digitalRead(STA_TE_PIN) == HIGH){
    RGB(0, 50, 0);  // Verde
    determinar_comando();
    enviar_comando_diferente();
    reenviar_comando();
    }
    else if(digitalRead(STA_TE_PIN) == LOW){
    RGB(80, 0, 255);  // Morado
    }
  }
}

// --------------
// SUBPROGRAMAS:
// --------------

void verificador_HC05(){
  while(digitalRead(STA_TE_PIN) == LOW){
    delay(250);
  }
}

void calibracion_MPU(){
  mpu.setFilterGyroCoef(0.75);  // Confianza en giroscopio
  mpu.setFilterAccCoef(0.25);  // Confianza en acelerómetro
  delay(3000);  // Tiempo para dejar quieto el MPU
  mpu.calcOffsets();  // Calibracion automatica del MPU
  for(int i = 1; i<=10; i++){
    mpu.update();  // Primeras lecturas después de calibrar
    suma_X_0 = suma_X_0 + mpu.getAngleX();  // Acumulacion de angulos iniciales eje X
    suma_Y_0 = suma_Y_0 + mpu.getAngleY();  // Acumulacion de angulos iniciales eje Y
    delay(50);
  }
  X_0 = suma_X_0 / 10;  // Guardar ángulo inicial X
  Y_0 = suma_Y_0 / 10;  // Guardar ángulo inicial Y
}

void determinar_comando(){
  if(Y > 20 && X < -40){
    comando = 1;  // Auto avanza girando a la derecha, solo si ya estaba avanzando
  }
  else if(Y < -20 && X < -40){
    comando = 2;  // Auto avanza girando a la izquierda, solo si ya estaba avanzando
  }
  else if(Y > 20 && X > 40){
    comando = 3;  // Auto retrocede girando a la derecha, solo si ya estaba retrocediendo
  }
  else if(Y < -20 && X > 40){
    comando = 4;  // Auto retrocede girando a la izquierda, solo si ya estaba retrocediendo
  }
  else if(X < -40){
    comando = 5;  // Auto solo avanza
  }
  else if(X > 40){
    comando = 6;  // Auto solo retrocede
  }
  else if(Y > 40){
    comando = 7;  // Auto gira en sentido horario
  }
  else if(Y < -40){
    comando = 8;  // Auto gira en sentido antihorario
  }
  else{
    comando = 0;  // Auto se detiene
  }
}

void enviar_comando_diferente(){
  if(comando != last_comando){
    hc05.println(comando);
    last_comando = comando;
    t = 0;
  }
}

void reenviar_comando(){
  t++;
  if(t > Tiempo_Reenvio){
    hc05.println(comando);
    t = 0;
  }
}

void verificar_dentro_rango(){
  if(X > 90 || X < -90 || Y > 90 || Y < -90){
    fuera_rango = 1;
    hc05.println(0);
    RGB(255, 0, 0);  // Rojo
  }
}

void RGB(int R, int G, int B){
  neo_RGB.setPixelColor(0, R, G, B);
  neo_RGB.show();
}