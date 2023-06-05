#include <Servo.h>
#include <IRremote.h>

int receptor = 13;

IRrecv irrecv(receptor);
decode_results codigo;

#define SERVO_PIN 9
#define BOMBA 12

Servo servoMotor;
bool servoMoved = false; // Saber si se movió o no
bool bombaMoved = false; // Saber si se movió o no


const int echo = 6;
const int trigger = 7;
long tiempo;
float distancia;

const int echo2 = 5;
const int trigger2 = 4;
long tiempo2;
float distancia2;

const int buzzerPin = 3;

void setup() {
  // Infrarrojo
  irrecv.enableIRIn();
  
  // Ultrasonico
  pinMode(echo, INPUT);
  pinMode(trigger, OUTPUT);

  // Ultrasonico 2
  pinMode(echo2, INPUT);
  pinMode(trigger2, OUTPUT);
  
  // Buzzer
  pinMode(buzzerPin, OUTPUT);
  
  // Servomotor
  servoMotor.attach(SERVO_PIN);
  
  // Boton
  pinMode(BOMBA, OUTPUT);
  
  servoMotor.writeMicroseconds(1500); // Posición inicial del servo (detenido)
  Serial.begin(9600);
}

void medir() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  tiempo = pulseIn(echo, HIGH, 10000);
  distancia = tiempo / 58;
  delay(10);
}

void medir2() {
  digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  tiempo2 = pulseIn(echo2, HIGH, 10000);
  distancia2 = tiempo2 / 58;
  delay(10);
}

void loop() {
  medir();
  medir2();
  Serial.println(irrecv.decode(&codigo));
  if (irrecv.decode(&codigo)) {
    
      switch (codigo.value) {
        case 0xFF6897: // Botón cero// ABRIR SERVOMOTOR
          if (distancia < 8) { // Si la distancia es menor a 8, hay obstrucción
            digitalWrite(buzzerPin, LOW);
            // Gira el servo 90 grados en una dirección
              servoMotor.writeMicroseconds(1400);
              delay(1000); // Ajusta este tiempo según la velocidad de tu servo

              // Detiene el servo
              servoMotor.writeMicroseconds(1500);
              servoMoved = true;
          }
          else if(distancia>8) {
            digitalWrite(buzzerPin, HIGH);
            Serial.println(distancia);
            delay(500);

          }
          
          break;
        case 0xFF30CF: // Botón uno// CERRAR SERVOMOTOR
          // Regresa el servo a la posición inicial
          if(servoMoved==true){
            servoMotor.writeMicroseconds(1600);
            delay(1000); // Ajusta este tiempo según la velocidad de tu servo
            servoMotor.writeMicroseconds(1500);
            servoMoved = false;
          }
          
          break;
        case 0xFF18E7: // Botón dos
        //apagar buzzer
          digitalWrite(buzzerPin, LOW);
          
          break;
          
        case 0xFF7A85: // Botón tres
          // Enciende el relé para activar la bomba
          if (distancia2 < 8) { // Si la distancia es menor a 8, hay obstrucción
            digitalWrite(BOMBA, HIGH);
            bombaMoved=true;
            delay(5000);
            digitalWrite(BOMBA, LOW);
            
          }else {
            digitalWrite(buzzerPin, HIGH);
            delay(500);
          }
          break;
        case 0xFF10EF://boton 4
        // Apaga el relé para detener la bomba
          if(bombaMoved==true){
            digitalWrite(BOMBA, LOW);
          }
          break;
    } 
    
    irrecv.resume();
    
  }
  
  delay(100);
}