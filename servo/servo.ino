/*
Adafruit Arduino - Lesson 14. Sweep
*/

#include <Servo.h> 

int servoPin = 10;
int rotationTime =170; 

Servo servo;  
 int angle;
void setup() 
{ 
  angle=0;
  servo.attach(servoPin); 
  servo.write(angle);  // set servo to mid-point
} 
 
 
void loop() 
{ 
  
                            
    servo.write(angle);     
          
    delay(1000);  
       
       angle+=10;   
  
 if(angle>180)angle=0;
} 
