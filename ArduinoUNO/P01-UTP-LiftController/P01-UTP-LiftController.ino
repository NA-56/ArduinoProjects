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

int carHeight; 

void setup()
{
    Serial.begin(9600);

    StepperSetUp();
    SR04SensorSetup();
    SG90ServoSetUp();
    ButtonsCofig(buttons);

}

void loop()
{
    carHeight = GetDistance();

    pressedButton = CheckForInput();
    if (lastButton==pressedButton)
    {
    
    }else{
        switch (pressedButton)
        {
        case 1:
            /* code */
            break;
        case 2:
            //code
            break;
        case 3:
            /* code */
            break;
        case 4:
            //code
            break;
        }
    }
    


    if (true)
    {
        //Make the motor spin in one direction 
        OneStep(false);
        //delay(2);
    }

    if (true)
    {
        //Close the door
        SG90ServoActivate(false);
        //Open the door 
        SG90ServoActivate(true);
    }
    
    
}

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

#pragma endregion



