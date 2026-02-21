#include <SoftwareSerial.h>

#define RX_PIN 8
#define TX_PIN 7
#define STA_TE_PIN 4
#define IN1_PIN A1
#define IN2_PIN A2
#define ENA_PIN 6
#define IN3_PIN A3
#define IN4_PIN A4
#define ENB_PIN 5
#define RED_PIN 11
#define GREEN_PIN 10
#define BLUE_PIN 9

SoftwareSerial BT(RX_PIN, TX_PIN);

int comando;

void config_PIN();
void verificador_BT();
void definir_accion();
void detenido();
void avanzar();
void retroceder();
void av_derecha();
void av_izquierda();
void re_derecha();
void re_izquierda();
void rotar_horario();
void rotar_antihorario();
void RGB(int R, int G, int B);

void setup(){
  Serial.begin(9600);
  BT.begin(115200);
  config_PIN();
  RGB(0, 0, 50);  // Azul
  verificador_BT();
  RGB(0, 50, 0);  // Verde
}

void loop(){
  if(BT.available()){
    comando = BT.parseInt();
    definir_accion();
  }
  if(digitalRead(STA_TE_PIN) == HIGH){
    RGB(0, 50, 0);  // Verde
  }
  else if(digitalRead(STA_TE_PIN) == LOW){
    RGB(20, 0, 70);  // Morado
    detenido();
  }
}

//--------------
// SUBPROGRAMAS:
//--------------

void verificador_BT(){
  while(digitalRead(STA_TE_PIN) == LOW){
    delay(250);
  }
}

void config_PIN(){
  pinMode(IN1_PIN, OUTPUT);
  pinMode(IN2_PIN, OUTPUT);
  pinMode(ENA_PIN, OUTPUT);
  pinMode(IN3_PIN, OUTPUT);
  pinMode(IN4_PIN, OUTPUT);
  pinMode(ENB_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(STA_TE_PIN, INPUT);
}

void definir_accion(){
  if(comando == 0){
    detenido();
  }
  else if(comando == 1){
    av_derecha();
  }
  else if(comando == 2){
    av_izquierda();
  }
  else if(comando == 3){
    re_derecha();
  }
  else if(comando == 4){
    re_izquierda();
  }
  else if(comando == 5){
    avanzar();
  }
  else if(comando == 6){
    retroceder();
  }
  else if(comando == 7){
    rotar_horario();
  }
  else if(comando == 8){
    rotar_antihorario();
  }
}

void detenido(){
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, HIGH);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENA_PIN, 0);
  analogWrite(ENB_PIN, 0);
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, LOW);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, LOW);
}

void avanzar(){
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, 200);
}

void retroceder(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, 200);
}

void av_derecha(){
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, 0);
}

void av_izquierda(){
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 0);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, 200);
}

void re_derecha(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, 0);
}

void re_izquierda(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, 0);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, 200);
}

void rotar_horario(){
  digitalWrite(IN1_PIN, HIGH);
  digitalWrite(IN2_PIN, LOW);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, LOW);
  digitalWrite(IN4_PIN, HIGH);
  analogWrite(ENB_PIN, 200);
}

void rotar_antihorario(){
  digitalWrite(IN1_PIN, LOW);
  digitalWrite(IN2_PIN, HIGH);
  analogWrite(ENA_PIN, 200);
  digitalWrite(IN3_PIN, HIGH);
  digitalWrite(IN4_PIN, LOW);
  analogWrite(ENB_PIN, 200);
}

void RGB(int R, int G, int B){
  analogWrite(RED_PIN, R);
  analogWrite(GREEN_PIN, G);
  analogWrite(BLUE_PIN, B);
}