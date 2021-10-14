#define Button1 2
#define Button2 3
#define Button3 4
#define Button4 5

int buttonState;
int buttons[4] = {Button1,Button2,Button3,Button4};

void setup()
{
    ButtonsCofig(buttons);
    Serial.begin(9600);

    
    
}

int lastButton = 0; 
int PressedButton = 0;

void loop()
{
    PressedButton = CheckForInput(); 
    if (lastButton == PressedButton)
    {
        
    }else {  
    
        Serial.print ("\n Button being pressed is the button: ");
        Serial.print ( PressedButton );
        Serial.print("\n");
        lastButton = PressedButton;
    }

}

#pragma region Complementary methods
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