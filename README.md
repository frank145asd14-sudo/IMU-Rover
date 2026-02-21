# IMU-Rover (Carro con Control de Movimiento Inercial)

## Objetivo General

Diseñar y desarrollar un carro robótico con control de movimiento inercial que permita manipular su desplazamiento mediante gestos e inclinación, demostrando una interfaz de control alternativa, intuitiva y accesible, aplicable tanto en entornos educativos como en soluciones de movilidad asistida.

## Objetivos Específicos

1. **Implementar una interfaz natural de control por gestos**
   Desarrollar un sistema que interprete los datos de la IMU (aceleración y giro) para permitir el control del vehículo sin botones ni joysticks, demostrando una alternativa innovadora de interacción hombre–máquina.

2. **Desarrollar un mecanismo de control intuitivo orientado a accesibilidad**
   Configurar el vehículo para que responda de manera suave y comprensible a la inclinación del controlador inercial, permitiendo su uso por personas con movilidad reducida o dificultades para manipular mandos tradicionales.

3. **Crear una plataforma educativa para el aprendizaje de sensores inerciales**
   Utilizar el carro como herramienta didáctica para enseñar el funcionamiento de una IMU, conceptos de física del movimiento (aceleración, inclinación, giro) y control de motores mediante microcontroladores.

4. **Integrar y probar la comunicación inalámbrica**
   Establecer una conexión robusta entre el módulo inercial y el carro mediante Bluetooth, asegurando una transmisión confiable de los datos de orientación para el control del movimiento.

5. **Validar el desempeño del sistema en distintos escenarios**
   Realizar pruebas de desplazamiento, respuesta al gesto e inclinación, precisión del control y estabilidad del vehículo para garantizar un funcionamiento eficiente en condiciones reales.

---

## Materiales del Proyecto

### 1. Mando Inercial (Controlador de Gestos)

* ESP32-S3 (alimentado a 5V mediante LM2596)
* Módulo Bluetooth HC-05
  (Se usa porque el Bluetooth del ESP32 no es compatible con el HC-05 del carro)
* Sensor MPU6050
* 2 baterías LiPo CL 523450 – 3.7V 1000 mAh (conectadas en serie)
* Regulador Step-Down LM2596 (para bajar a 5V)
* Protoboard pequeño (para interconexiones)
* Jumpers hembra–macho y macho–macho
* Estructura hecha con bajalenguas
  (para unir baterías + LM2596 + protoboard en un solo módulo compacto)

### 2. Carro (Receptor + Actuadores)

* Arduino Nano
* Módulo Bluetooth HC-05
* Convertidor de Nivel Lógico Bidireccional 3.3V ↔ 5V
  (para comunicación segura Arduino ↔ HC-05)
* Driver L298N (control para 4 motores)
* 4 Motores BO + 4 ruedas
* 2 baterías Li-Ion BRC18650 – 3.7V 1600 mAh (en serie)
  (alimentación directa del L298N para los motores)
* 2 baterías LiPo CL 523450 – 3.7V 1000 mAh (en serie)
  (exclusivas para el Arduino Nano)
* Regulador Step-Down LM2596 (para bajar a 5V para el Nano)
* Chasis de triplay rectangular pintado negro, con:

  * Prismas/bloques inferiores para atornillar motores
  * Dos orificios laterales para pasar los cables de los motores
* Tornillos
* Protoboard pequeño (para conexiones internas del carro)
* Jumpers hembra–macho y macho–macho

---

## Lista de Movimientos del Carro (Versión Final)

### 0. Posición neutra

* Mano paralela al piso (sin inclinación en X ni Y)
  → Carro se detiene

### 1. Movimiento lineal

* **Inclinación hacia adelante**
  Dedos más abajo que la muñeca
  → Carro avanza

* **Inclinación hacia atrás**
  Dedos más arriba que la muñeca
  → Carro retrocede

### 2. Giros sobre su propio eje

* **Inclinación hacia la derecha**
  Meñique más abajo que el pulgar
  → Carro gira en sentido horario (rota en su eje hacia la derecha)

* **Inclinación hacia la izquierda**
  Pulgar más abajo que el meñique
  → Carro gira en sentido antihorario (rota en su eje hacia la izquierda)

### 3. Movimientos combinados

* **Adelante + Derecha**
  Dedos abajo + meñique abajo
  → Avanza girando a la derecha

* **Adelante + Izquierda**
  Dedos abajo + pulgar abajo
  → Avanza girando a la izquierda

* **Atrás + Derecha**
  Dedos arriba + meñique abajo
  → Retrocede girando a la derecha

* **Atrás + Izquierda**
  Dedos arriba + pulgar abajo
  → Retrocede girando a la izquierda

