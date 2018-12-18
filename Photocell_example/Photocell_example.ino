

int photocellInput = 0;
 
void setup()  {

    Serial.begin(9600);
      while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
}
 
 
void loop()  {
 
  photocellInput = analogRead(photocellInput); // Divides input 0-1023 to resemble to 0-255
 
   Serial.println(photocellInput);
  // The delay can be change to get the desired dimming effect
  delay(150);                            
}


