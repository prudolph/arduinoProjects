
#include <Adafruit_NeoPixel.h>

//Accelerometer Pins
const int x = A0; // X pin connected to Analog 3
const int y = A1; // Y pin connected to Analog 4
const int z = A2; // Z pin connected to Analog 5

const int ledPin = 8; // Z pin connected to Analog 5


int tolerance=40; // Sensitivity of the movement
boolean calibrated=false; // When accelerometer is calibrated - changes to true 
boolean moveDetected=false; // When motion is detected - changes to true
boolean breakingDetected=false;


//Accelerometer limits
int xMin; //Minimum x Value
int xMax; //Maximum x Value
int xVal; //Current x Value

int yMin; //Minimum y Value
int yMax; //Maximum y Value
int yVal; //Current y Value

int zMin; //Minimum z Value
int zMax; //Maximum z Value
int zVal; //Current z Value

unsigned long movedStartTime;

unsigned long movementTimeout = 10000;

 Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, ledPin, NEO_GRB + NEO_KHZ800);
void setup(){
 //Begin Serial communication
 Serial.begin(9600);

  calibrateAccel();
 strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 
}



void loop(){
    Serial.println();
   Serial.print(moveDetected);
 // Once the accelerometer is calibrated - check for movement 
 if(calibrated){
   if(checkMotion()){
     moveDetected=true;
     movedStartTime= millis();
   } 
 }
 
  if( (millis() - movedStartTime)>movementTimeout ){
    moveDetected=false;
  }


if(moveDetected){
  
  frontLights();
  rearLights(breakingDetected);
  strip.setBrightness(50);
  strip.show();
}else{
  strip.setBrightness(0);
  strip.show();
}
 
 
 delay(100);
 }
 





// Function used to calibrate the Accelerometer
void calibrateAccel(){
 // reset alarm
 moveDetected=false;
 
 //initialise x,y,z variables
 xVal = analogRead(x);
 xMin = xVal;
 xMax = xVal;
 
 yVal = analogRead(y);
 yMin = yVal;
 yMax = yVal;
 
 zVal = analogRead(z);
 zMin = zVal;
 zMax = zVal;
 

 
 //calibrate the Accelerometer (should take about 0.5 seconds)
 for (int i=0; i<50; i++){
 // Calibrate X Values
 xVal = analogRead(x);
 if(xVal>xMax){
 xMax=xVal;
 }else if (xVal < xMin){
 xMin=xVal;
 }

 // Calibrate Y Values
 yVal = analogRead(y);
 if(yVal>yMax){
 yMax=yVal;
 }else if (yVal < yMin){
 yMin=yVal;
 }

 // Calibrate Z Values
 zVal = analogRead(z);
 if(zVal>zMax){
 zMax=zVal;
 }else if (zVal < zMin){
 zMin=zVal;
 }

 //Delay 10msec between readings
 delay(10);
 }
 
 //End of calibration sequence sound. ARMED.
 printValues(); //Only useful when connected to computer- using serial monitor.
 calibrated=true;
 
}



//Function used to detect motion. Tolerance variable adjusts the sensitivity of movement detected.
boolean checkMotion(){
 boolean tempB=false;
 xVal = analogRead(x);
 yVal = analogRead(y);
 zVal = analogRead(z);
 
 if(xVal >(xMax+tolerance)||xVal < (xMin-tolerance)){
 tempB=true;
 Serial.print("X  Moved ");
 Serial.println(xVal);
 }
 
 if(yVal >(yMax+tolerance)||yVal < (yMin-tolerance)){
 tempB=true;
 Serial.print("Y Moved = ");
 Serial.println(yVal);
 }
 
 if(zVal >(zMax+tolerance)||zVal < (zMin-tolerance)){
 tempB=true;
 
 
 if(zVal < (zMin-tolerance)){
   breakingDetected=true;
 }
 
 Serial.print("Z Moved = ");
 Serial.println(zVal);
 }else{
  breakingDetected=false;
 }
 
 return tempB;
}
 




// Prints the Sensor limits identified during Accelerometer calibration.
// Prints to the Serial monitor.
void printValues(){
 Serial.print("xMin=");
 Serial.print(xMin);
 Serial.print(", xMax=");
 Serial.print(xMax);
 Serial.println();
 
 Serial.print("yMin=");
 Serial.print(yMin);
 Serial.print(", yMax=");
 Serial.print(yMax);
 Serial.println();
 
 Serial.print("zMin=");
 Serial.print(zMin);
 Serial.print(", zMax=");
 Serial.print(zMax);
 Serial.println();
 
 Serial.println("------------------------");
}


void frontLights(){
  for(int i =0;i<6;i++){
   strip.setPixelColor(i, 255, 255, 255);
  }
}

void rearLights(boolean breaking){
   if(breaking){
     for(int i =6;i<12;i++){
       strip.setPixelColor(i, 255, 0, 255);
      }
   }else{
    for(int i =6;i<12;i++){
     strip.setPixelColor(i, 255, 0, 0);
    }
   }
}

