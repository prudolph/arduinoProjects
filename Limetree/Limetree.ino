
int thresholdUp = 400;
int thresholdDown = 250;

// We are setting up the pin A0 on the redboard to be our sensor
// pin input:

int sensorPin = 2;
int sensorPower = 0;
int ledPin =1;


void setup() {
  pinMode(sensorPower, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(sensorPin,INPUT);
  
  // put your setup code here, to run once:
   //Serial.begin(9600); // set up serial port for 9600 baud (speed)
  //delay(500); // wait for display to boot up
  
  blink(10,500);
}

void loop() {
  
  
   digitalWrite(sensorPower, HIGH);   // Turn Sensor on
   delay(500);                  // waits for a second
   int sensorValue = analogRead(1);
   digitalWrite(sensorPower, LOW);   //Turn Sensor off
  
    //Serial.write("Water Level: ");
    //Serial.print(sensorValue);
    if (sensorValue <= thresholdDown){
      //Serial.print("Dry, Water it!");
     
       digitalWrite(ledPin, HIGH);
      
     } 
     
    else if (sensorValue >= thresholdUp){
    
     // Serial.print("Wet, Leave it!");
   
      digitalWrite(ledPin, LOW);
       
     
    } 
     //Serial.println("");
 
   delay(30000);                  // waits for 30 seconds
   
}

void blink(int cnt,int time){
  for(int i =0;i<cnt;i++){
     digitalWrite(ledPin, HIGH);
     delay(time); 
     digitalWrite(ledPin, LOW);
     delay(time); 
   }
}

