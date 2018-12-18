/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
int windDirectionPin = A0;
int windSpeedPin = A1;

 volatile int half_revolutions =0;
 unsigned int rpm =0;
 unsigned long timeold =0;


  
   
   
void rpm_fun()
 {
   half_revolutions++;
   //Each rotation, this interrupt function is run twice
 }

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  
   attachInterrupt(0, rpm_fun, RISING);

  pinMode(windDirectionPin, INPUT);     
  pinMode(windSpeedPin, INPUT); 
 
}

// the loop routine runs over and over again forever:
void loop() {
  
  if (half_revolutions >= 20) { 
     //Update RPM every 20 counts, increase this for better RPM resolution,
     //decrease for faster update
     rpm = 30*1000/(millis() - timeold)*half_revolutions;
     timeold = millis();
     half_revolutions = 0;
     Serial.println(rpm,DEC);
   }


 
  // print out the value you read:
 Serial.print("Direction ");
 Serial.println( getWindDirection() );


 Serial.print("Speed ");
 Serial.println( getWindSpeedRPMs());

// Serial.print(" ");
//Serial.println(revolutions );
//revolutions=0;
  delay(100);        // delay in between reads for stability
  
}

String getWindDirection(){
   // read the input on analog pin 0:
  int degree = analogRead(windDirectionPin)/2;

  Serial.print(degree );
   Serial.print(" "  );
  float dir = map(degree,0,522,0,360);
   Serial.print(" "  );
  Serial.print(dir );
   
   if(               dir< 11.25)   return "N";
   else if(dir>11.25  &&  dir< 33.75)   return "NNE";
   else if(dir>33.75  &&  dir< 56.25)   return "NE";
   else if(dir>56.25  &&  dir< 78.75)   return "ENE";
   else if(dir>78.75  &&  dir< 101.25)  return "E";
   else if(dir>101.25 &&  dir< 123.75)  return "ESE";
   else if(dir>123.75 &&  dir< 146.25)  return "SE";
   else if(dir>146.25 &&  dir< 168.75)  return "SSE";
   else if(dir>168.75 &&  dir< 191.25)  return "S";
   else if(dir>161.25 &&  dir< 213.75)  return "SSW";
   else if(dir>213.75 &&  dir< 236.25)  return "SW";
   else if(dir>236.25 &&  dir< 258.75)  return "WSW";
   else if(dir>258.75 &&  dir< 281.25)  return "W";
   else if(dir>281.25 &&  dir< 303.75)  return "WNW";
   else if(dir>303.75 &&  dir< 326.25)  return "NW";
   else if(dir>326.25 &&  dir< 348.75)  return "NNW";
  else return "Bad Data" ;
}


int getWindSpeedRPMs(){
  
  
  unsigned long time=millis();
  
  int count =0;
  while((millis()-time)< 10000){
    
      int windSpeedValue = analogRead(windSpeedPin);

    
     if(windSpeedValue == 0)count++; 
     
     delay(50);
  }
    
 return count;
  
}


