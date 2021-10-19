//This script will only work to display the numers from 1 to 4 and where 
//The UpperRightVerticalLine will be connected to Voltage source all the time

#define PIN0 A0
#define PIN1 A1
#define PIN2 A2
#define PIN3 A3
#define PIN4 A4

uint8_t AnalogPins[] = {PIN0,PIN1,PIN2,PIN3,PIN4 };

//PIN0 should be connected to the UpperHorizontalLine and the LowerHorizontalLine
//PIN1 should be connected to the MiddleHorizontalLine
//PIN2 should be connected to the LowerLeftVerticalLine
//PIN3 should be connected to the LowerRightVerticalLine

void setup()
{
    PinsCofig(AnalogPins, OUTPUT);    
}

int i = 0; 
void loop()
{
    if (i==0)
    {
        DisplayFloor(4);
        i++;
    }else{

    }
    
}

#pragma region Complementary methods

void PinsCofig(uint8_t pins[],uint8_t mode){
    
    for (int i = 0; i < sizeof(pins)/sizeof(pins[0]) ; i++)
    {
        pinMode(pins[i], mode);
    }
     
}

void DisplayFloor(int floorNumber){

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