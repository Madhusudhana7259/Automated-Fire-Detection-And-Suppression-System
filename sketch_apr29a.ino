Arduino:
#include <Servo.h>

#define in1 9

#define servoPin 11



Servo myservo;  // Create a servo object


int data;
int pos=0;

bool check = false;
bool c = true;
bool up = false;



void re()
{
  data = Serial.read();
  if (data==1)
  {
    check=true;
  }
  else if(data==0){
    check=false;
  }
  else
  {
    check = true;
  }
}  

void setup() {
  Serial.begin(300);
  // Set all the motor control pins to outputs
  
  pinMode(in1, OUTPUT);
  //pinMode(in2, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(in1, HIGH);
  

  myservo.attach(servoPin);  // Attach the servo to the pin
  myservo.write(0);  // Set initial position of the servo to 0 degrees
}
void loop() {
  
  if (Serial.available()) {
    
    re();
    if (check)
  {
    if (myservo.attached())
      myservo.detach();
    digitalWrite(in1, LOW);
    delay(3000);
  }
  else
  {
    digitalWrite(in1, HIGH);
    
    if (!myservo.attached())
      myservo.attach(servoPin);
    else
    {
      if (!up)
      {
        do
        {
          re();
          pos++;
          myservo.write(pos);
          
          if (pos == 180) up = true;
          if (check)
          {
            myservo.detach();
            break;
          }
        }
        while (pos <= 180);
      }
      else
      {
        do
        {
          re();
          pos--;
          myservo.write(pos);
          if (pos == 0) up = false;
          if (check)
          {
            myservo.detach();
            break;
          }
        }
        while (pos >= 0); 
      }
  }
    
     }
    }
  }