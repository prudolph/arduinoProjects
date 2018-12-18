

int photocellInput = 0;
 
void setup()  {
  pinMode(ledPin, OUTPUT);
    Serial.begin(9600);
}
 
 
void loop()  {
 
  photocellInput = (analogRead(photocellInput)/4); // Divides input 0-1023 to resemble to 0-255
 
   Serial.println(photocellInput);
  // The delay can be change to get the desired dimming effect
  delay(20);                            
}


