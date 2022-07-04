// la libreria MPU6050.h necesita I2Cdev.h, I2Cdev.h necesita Wire.h
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// La dirección del MPU6050 puede ser 0x68 o 0x69, dependiendo 
// del estado de AD0. Si no se especifica, 0x68 estará implicito
MPU6050 sensor;

// Valores RAW (sin procesar) del acelerometro y giroscopio en los ejes x,y,z
int ax, ay, az;

float loop_timer;
int t, loop_counter, periodo;

void setup() 
{
  Serial.begin(115200);    //Iniciando puerto serial
  Wire.begin();           //Iniciando I2C  
  sensor.initialize();    //Iniciando el sensor

  if (sensor.testConnection()) Serial.println("Sensor iniciado correctamente");
  else Serial.println("Error al iniciar el sensor");
}

void loop() {
 
  while (micros() - loop_timer < 5000)
  {  
    loop_timer = micros();
    
    // Leer las aceleraciones
    sensor.getAcceleration(&ax, &ay, &az);
    float ax_m_s2 = ax * (9.81/16384.0);
    float ay_m_s2 = ay * (9.81/16384.0);
    float az_m_s2 = az * (9.81/16384.0);
    
    // Enviamos las señales a la compu por el puerto serie. MANTENER SIEMPRE ESTE FORATO!! Podeis añadir mas variables.
    if (loop_counter == 0)Serial.print(ax_m_s2);
    if (loop_counter == 1)Serial.print("\t");
    if (loop_counter == 2)Serial.print(ay_m_s2);
    if (loop_counter == 3)Serial.print("\t");
    if (loop_counter == 4)Serial.println(az_m_s2);

    loop_counter ++;
    if (loop_counter == 5)loop_counter = 0;

    t++;
    if (t == 10)t = 0;
    delay(20);
  }
}