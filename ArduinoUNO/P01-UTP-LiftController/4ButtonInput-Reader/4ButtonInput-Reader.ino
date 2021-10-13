#define Button1 2
#define Button2 3
#define Button3 4
#define Button4 5

int buttonState = 0;
int buttonBeingPressed=0;
int buttons[4];

void setup()
{
    buttons[0] = Button1;
    buttons[1] = Button2;
    buttons[2] = Button3;
    buttons[3] = Button4;

    ButtonsCofig(buttons);
   
    Serial.begin(9600);
    
}

void loop()
{
    buttonBeingPressed = -1;
   for (int i = 0; i < sizeof(buttons) ; i++)
    {
        buttonState = digitalRead(buttons[i]);

        if (buttonState == HIGH)
        {
            buttonBeingPressed = i+1;
            Serial.print("\n Button being pressed is the button: ");
            Serial.print(i+1);
            break;
        }
    }

}

#pragma region Complementary methods
void ButtonsCofig(int buttons[]){
    
    for (int i = 0; i < sizeof(buttons) ; i++)
    {
        pinMode(buttons[i], INPUT);
    }
     
}
#pragma endregion