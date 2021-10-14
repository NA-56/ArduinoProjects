#include <Servo.h>

Servo servo; 

void setup()
{
    pinMode(5,INPUT);
    pinMode(7,INPUT);
    servo.attach(2);
    servo.write(0);
    delay(2000);
}

void loop()
{
    if(digitalRead(5)==HIGH)
    {
        servo.write(90);
        delay(1000);
        
    }
     if(digitalRead(7)==HIGH)
    {
        servo.write(0);
        delay(1000);
        
    }
}