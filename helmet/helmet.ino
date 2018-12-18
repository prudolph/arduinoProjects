
#include<VirtualWire.h>
#include <Adafruit_NeoPixel.h>

#define LEDPIN 13
#define BRAKEPIN 8
#define LEFTPIN 9
#define RIGHTPIN 10

#define TRANSPIN 3




// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, LEDPIN, NEO_GRB + NEO_KHZ800);

  uint32_t redColor = strip.Color(255, 0, 0);
  uint32_t amberColor = strip.Color(255, 255, 0);
  uint32_t offColor = strip.Color(0, 0, 0);
  
bool sendON=true;
void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // Initialize all pixels to 'off
  pinMode(BRAKEPIN, INPUT);
   pinMode(LEFTPIN, INPUT); 
   pinMode(RIGHTPIN, INPUT);
    pinMode(TRANSPIN, OUTPUT);  


// Initialize the IO and ISR
vw_setup(2000); // Bits per sec
}

void loop() {
 
 send("0001");
 // read the states of the Reciver:
 int brakeState = digitalRead(BRAKEPIN);
 int leftState = digitalRead(LEFTPIN);
 int rightState = digitalRead(RIGHTPIN);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (brakeState == HIGH) {
    brake();
  } 
  
  else if(leftState==HIGH){
    turn(true);
  }
  
  else if(rightState==HIGH){
    turn(false);
  }else{
  off();
  }
  
}

//TRANSMIT
void send (char *message)
{
vw_send((uint8_t *)message, strlen(message));
vw_wait_tx(); // Wait until the whole message is gone
}

///LIGHT SCHEMES
void off(){
for(int i =0;i<=5;i++){
  strip.setPixelColor(i, offColor);
}
  strip.show(); 

}


void brake(){

for(int i =0;i<=5;i++){
  strip.setPixelColor(i, redColor);
}
  strip.show(); 

}
// true = left false = right
void turn(bool dir){
 
  if(strip.getPixelColor(0)==offColor){  
    if(dir){
    for(int i =0;i<=5;i++){
      strip.setPixelColor(i, amberColor);
      delay(100);
      strip.show();
    }
    }else{
    
    for(int i =5;i>=0;--i){
      strip.setPixelColor(i, amberColor);
      delay(100);
      strip.show();
    }
    }
    
  }else{
      for(int i =0;i<=5;i++){
        strip.setPixelColor(i, offColor);
      }
     strip.show();
}
}

