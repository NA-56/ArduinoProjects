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
float distance;

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

#pragma region Main variable declaration

#define Level1 2.5  //cm
#define Level2 14 //cm
#define Level3 29 //cm
#define Level4 41 //cm

int currentHeight = 0;


#pragma endregion

void setup()
{
    Serial.begin(9600);

    StepperSetUp();
    SR04SensorSetup();
    //SG90ServoSetUp();
    ButtonsCofig(buttons);

}

void loop()
{
    pressedButton = CheckForInput();
    if (lastButton==pressedButton)
    {
        
    } 
    else    
    {
        Serial.print ("\n Button being pressed is the button: ");
        Serial.print ( pressedButton );
        Serial.print("\n");

        currentHeight = GetDistance();
        Serial.print ("\n The distance is: ");
        Serial.print ( currentHeight );
        Serial.print("\n");

        switch (pressedButton)
        {
        case 2:
            if (currentHeight == Level1)
            {
                
            }
            else{
                if (currentHeight > Level1)
                {
                    while (currentHeight > Level1)
                    {
                        OneStep(true); //Go down
                        currentHeight=GetDistance();
                    }
                }else
                {
                    Serial.print("Hay un error con el nivel 1");
                }
            }
        break;

        case 3:
            if (currentHeight == Level2)
            {
                
            }
            else{
                if (currentHeight > Level2)
                {
                    while (currentHeight > Level2)
                    {
                        OneStep(true); //Go down
                        currentHeight=GetDistance();
                    }
                }else
                {
                   if (currentHeight < Level2)
                    {
                        while (currentHeight < Level2)
                        {
                            OneStep(false); //Go up
                            currentHeight=GetDistance();
                        }
                    }
                    else
                    {
                    Serial.print("Hay un error con el nivel 2");
                    }
                }
            }
        break;

        case 4: 
            if (currentHeight == Level3)
            {
                
            }
            else{
                if (currentHeight > Level3)
                {
                    while (currentHeight > Level3)
                    {
                        OneStep(true); //Go down
                        currentHeight=GetDistance();
                    }
                }else
                {
                   if (currentHeight < Level3)
                    {
                        while (currentHeight < Level3)
                        {
                            OneStep(false); //Go up
                            currentHeight=GetDistance();
                        }
                    }
                    else
                    {
                    Serial.print("Hay un error con el nivel 3");
                    }
                }
            }
        break;

        case 5:
            if (currentHeight == Level4)
            {
                
            }
            else{
                if (currentHeight < Level4)
                {
                    while (currentHeight < Level4)
                    {
                        OneStep(false); //Go up
                        currentHeight=GetDistance();
                    }
                }else
                {
                    Serial.print("Hay un error con el nivel 4");
                }
            }
        break;

        default:
        Serial.print("Hay un error general, este es el caso default");
            break;
        }
        
        lastButton = pressedButton;
    }
        
}


#pragma region Complementary Functions

    #pragma region Stepper Functions

    void StepperSetUp() {
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
        pinMode(echoPin,INPUT);


    }

    float GetDistance()
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



