
const int xAxisPin = A0; 
int xMaxValue=5;
int xMinValue=685;
double movementTimestamp;
// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
   // while the serial stream is not open, do nothing:
   while (!Serial);
   
    //   pinMode(xAxisPin, OUTPUT);
  movementTimestamp = millis();
}

// the loop routine runs over and over again forever:
void loop() {
 

  int xAxisValue = analogRead(xAxisPin);
  
  if(xAxisValue<xMinValue){xMinValue=xAxisValue;}
    if(xAxisValue>xMaxValue){xMaxValue=xAxisValue;}
  
  int mappedXValue = map(xAxisValue, xMinValue, xMaxValue, -100, 100);
 
  Serial.println(mappedXValue);
 
  
  if(abs(mappedXValue)>50){
    movementTimestamp = millis();
     Serial.println("\t\tMove");
  }
  delay(1);        // delay in between reads for stability
}
