// Librerias I2C para controlar el mpu6050
// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include "math.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;

#define STEPPER_PIN_1 8
#define STEPPER_PIN_2 9
#define STEPPER_PIN_3 10
#define STEPPER_PIN_4 11
int step_number = 0;
float ax_m_s2;
float ay_m_s2;
float az_m_s2;
float tanValue;
float angleInPlaneXY;

float loop_timer;
int t, loop_counter, periodo;

void setup() {
  Serial.begin(115200);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");


  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  
}


void loop() {
 
  while (micros() - loop_timer < 5000);  
  loop_timer = micros();
  
  // Leer las aceleraciones
  sensor.getAcceleration(&ax, &ay, &az);
  ax_m_s2 = ax * (9.807/16384.0);
  ay_m_s2 = ay * (9.807/16384.0);
  az_m_s2 = az * (9.807/16384.0);
  tanValue = (ay_m_s2)/(sqrt(pow(ax_m_s2,2)+ pow(az_m_s2,2)));
  angleInPlaneXY = atan(tanValue);
  
  Serial.print(angleInPlaneXY);
  Serial.print("\n");

  if (angleInPlaneXY < -0.1)
  {
      OneStep(true);
  }
  
  if (angleInPlaneXY > 0.1)
  {
      OneStep(false);
  }
  
  delay(2);  

}


void OneStep(bool dir){
    if(dir){
        switch(step_number)
        {
            case 0:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 3:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        } 
      }else{
        switch(step_number)
        {
            case 0:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
            case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
            case 3:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
       } 
  }
step_number++;
  if(step_number > 3){
    step_number = 0;
  }
}
