#pragma region  Stepper pin & variable declaration 
#define STEPPER1 8
#define STEPPER2 9
#define STEPPER3 10
#define STEPPER4 11

int stepNumber = 0; 
#pragma endregion
 
#pragma region HC-SR04 Sensor pin & variable declaration
#define trigPin 12
#define echoPin 13

long duration;
int distance;

#pragma endregion

#pragma region SG90Servo pin & variable declaration

#define ServoPin 7
#include <Servo.h>
Servo servo;

#pragma endregion 

#pragma region ButtomInputs pin & variable declaration

#define Button1 2 
#define Button2 3
#define Button3 4
#define Button4 5 

int buttonState;
int buttons[4] = {Button1,Button2,Button3,Button4};

int lastButton = 0;
int pressedButton = 0;

#pragma endregion

#pragma region 5011AS-NumberDisplay pin & variable declaration

#define PIN0 A0
#define PIN1 A1
#define PIN2 A2
#define PIN3 A3
#define PIN4 A4

uint8_t AnalogPins[] = {PIN0,PIN1,PIN2,PIN3,PIN4 };

#pragma endregion 

int carHeight; 

void setup()
{
    Serial.begin(9600);

    StepperSetUp();
    SR04SensorSetup();
    SG90ServoSetUp();
    ButtonsCofig(buttons);
    NumberDisplayCofig(AnalogPins,OUTPUT);

}

void loop()
{

    
}

#pragma region Seconday Functions





#pragma endregion 


#pragma region Complementary Functions

    #pragma region Stepper Functions

    void StepperSetUp()
    {
        pinMode(STEPPER1,OUTPUT);
        pinMode(STEPPER2,OUTPUT);
        pinMode(STEPPER3,OUTPUT);
        pinMode(STEPPER4,OUTPUT);
    }

    void OneStep(bool dir)
    {
        if(dir)
        {
            switch(stepNumber)
            {
                case 0:
                digitalWrite(STEPPER1, HIGH);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, LOW);
                break;
                case 1:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, HIGH);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, LOW);
                break;
                case 2:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, HIGH);
                digitalWrite(STEPPER4, LOW);
                break;
                case 3:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, HIGH);
                break;
            } 
        }
        else
        {
            switch(stepNumber)
            {
                case 0:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, HIGH);
                break;
                case 1:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, HIGH);
                digitalWrite(STEPPER4, LOW);
                break;
                case 2:
                digitalWrite(STEPPER1, LOW);
                digitalWrite(STEPPER2, HIGH);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, LOW);
                break;
                case 3:
                digitalWrite(STEPPER1, HIGH);
                digitalWrite(STEPPER2, LOW);
                digitalWrite(STEPPER3, LOW);
                digitalWrite(STEPPER4, LOW);
            } 
        }

        stepNumber++;

        if(stepNumber > 3)
        {
            stepNumber = 0;
        }

        delay(2);
    }

    #pragma endregion

    #pragma region HC-SR04 Sensor Fuctions

    void SR04SensorSetup()
    {

        pinMode(trigPin,OUTPUT);
        pinMode(echoPin,OUTPUT);


    }

    int GetDistance()
    {
        digitalWrite(trigPin,LOW);
        delayMicroseconds(2);

        digitalWrite(trigPin,HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin,LOW);

        duration = pulseIn(echoPin,HIGH);
        distance = duration * 0.034/2;

        return distance;
    }

    #pragma endregion

    #pragma region SG90Servo Functions

    void SG90ServoSetUp(){
        
        servo.attach(ServoPin);
        servo.write(0);
        delay(2000);
    }

    void SG90ServoActivate(bool action){

        //Action is going to comunicate what the door does
        // TRUE = opens, FALSE = closes
        if (action)
        {
            servo.write(90);
            delay(1000);
        }else{
            servo.write(0);
            delay(1000);
        }
        
    }

    #pragma endregion

    #pragma region ButtomInput Fuctions

    void ButtonsCofig(int buttons[]){
        
        for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]) ; i++)
        {
            pinMode(buttons[i], INPUT);
        }
        
    }

    int CheckForInput(){
            buttonState = 0;

        for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]) ; i++)
        {
            buttonState = digitalRead(buttons[i]);

            if (buttonState == HIGH )
            {   
                return buttons[i];
            }
        }
    }


    #pragma endregion

    #pragma region 5011AS-NumberDisplay Functions

    void NumberDisplayCofig(uint8_t pins[],uint8_t mode)
    {
            for (int i = 0; i < sizeof(pins)/sizeof(pins[0]) ; i++)
        {
            pinMode(pins[i], mode);
        }
    }

    void DisplayFloor(int floorNumber)
    {

        switch (floorNumber)
        {
        case 1:

            digitalWrite(PIN0,LOW);
            digitalWrite(PIN1,LOW);
            digitalWrite(PIN2,LOW);
            digitalWrite(PIN3,HIGH);
            digitalWrite(PIN4,LOW);

            break;
        case 2:

            digitalWrite(PIN0,HIGH);
            digitalWrite(PIN1,HIGH);
            digitalWrite(PIN2,HIGH);
            digitalWrite(PIN3,LOW);
            digitalWrite(PIN4,LOW);

            break;
        case 3:

            digitalWrite(PIN0,HIGH);
            digitalWrite(PIN1,HIGH);
            digitalWrite(PIN2,LOW);
            digitalWrite(PIN3,HIGH);
            digitalWrite(PIN4,LOW);

            break;

        case 4:

            digitalWrite(PIN0,LOW);
            digitalWrite(PIN1,HIGH);
            digitalWrite(PIN2,LOW);
            digitalWrite(PIN3,HIGH);
            digitalWrite(PIN4,HIGH);
            
            break;
        }
    }

    #pragma endregion

#pragma endregion



