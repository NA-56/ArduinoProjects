#define trigPin 12
#define echoPin 13

long duration;
int distance; 

void setup()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(2,INPUT);

    Serial.begin(9600);
    
}

void loop()
{
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration*0.034/2;

    if (true)
    {
          Serial.print("\n Distance: ");
        Serial.print(distance);
    }
    

  

}