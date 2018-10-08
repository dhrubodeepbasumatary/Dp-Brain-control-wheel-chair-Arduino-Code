#include <Brain.h>

#define RELAY1  4
#define RELAY3  3

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;  

long duration;
int distance;

int med_value;
int attValue;
//int allvalues[11];
int low_beta;
Brain brain(Serial);


void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); 
}

int count= 0;
void loop() {

  count = count +1;
  
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH); 
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;

    
//   if(distance<10)
//   {
//    digitalWrite(RELAY1,LOW);
//    digitalWrite(RELAY3,LOW);
//    
//   }

    if(distance<20){
      digitalWrite(RELAY1,LOW);
      digitalWrite(RELAY3,LOW);
      delay(3000);
      Serial.println("Less distance\n"); 
    }


    else{
      if(brain.update())
  {

    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);
       
    Serial.println(brain.readCSV());
    attValue = brain.readAttention();
    Serial.println(attValue);
    Serial.println(med_value);
    if(attValue>=5 and attValue<=50)
    {
      digitalWrite(RELAY1,HIGH);
      digitalWrite(RELAY3,HIGH); 
      Serial.println("forward");
      delay(3000);
    }
    if(attValue>50 && attValue <70)
    {
      digitalWrite(RELAY3,HIGH); 
      digitalWrite(RELAY1,LOW);
      Serial.println("left");
      delay(3000);
    }
    else if(attValue>=70 && attValue<=100)
    {
      digitalWrite(RELAY1,HIGH); 
      digitalWrite(RELAY3,LOW);
      Serial.println("Right");
      delay(3000);
    }
    else
    {
      digitalWrite(RELAY1,LOW); 
      digitalWrite(RELAY3,LOW);
      Serial.print("stop");
    }
  }
}

}

