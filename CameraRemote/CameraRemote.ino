#include <ESP8266WebServer.h>

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal

#include <SimpleTimer.h>
int ShutterPin = 15;

ESP8266WebServer server(80);
//Function Delcarations
int handleReq(String req);
void handleRoot();
void handleNotFound();
void handleFormSubmit();


SimpleTimer triggerTimer;
int triggerTimerId;
float triggerInterval=10000;



const String HTML_HEADER =
"<!DOCTYPE HTML>"
"<html>"
"<head>"
"<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
"<title>Feeder Configuration</title>"
"<style>"
"\"body { background-color: #808080; font-family: Arial, Helvetica, Sans-Serif; Color: #000000; }\""
"</style>"
"<script>"
 "function buttonCallback(String mode ){"
 "console.log(\"Mode\"+mode);"
 "var xhttp = new XMLHttpRequest();"
 "xhttp.onreadystatechange = function() {"
 "xhttp.open(\"GET\", mode, true); xhttp.send();"
 "}"
"</script>"
"</head>"
"<body>";

const String HTML_FOOTER = 
  "</body></html>";

const String HTML_FORM =
"<FORM action=\"/setInterval\" method=\"post\">"
"<P>"
"<INPUT type=\"number\" name=\"interval\" value=\"1\">Interval(seconds)<BR>"
"<INPUT type=\"submit\" value=\"Send\"> <INPUT type=\"reset\">"
"</P>"
"</FORM>";
void setup() {
  Serial.begin(9600);
  delay(2000);
  
  Serial.println("BOOTING...");


  //Setup as AP

  WiFi.softAP("CameraRemote", "password");

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  Serial.println("connected-------------)");

  // Start TCP (HTTP) server
  server.on("/", handleRoot);
  server.on("/setInterval", setInterval);
  server.onNotFound(handleNotFound);
  
  
  server.begin();
  
  Serial.println("Server started");
  
  // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);


  pinMode(ShutterPin,OUTPUT);

  triggerTimerId = triggerTimer.setInterval(triggerInterval, triggerCamera);

  
}

void loop() {

   server.handleClient();
   triggerTimer.run();
   delay(10);
   
}

void triggerCamera(){
  
  
  digitalWrite(ShutterPin,HIGH); 
  delay(500);
  digitalWrite(ShutterPin,LOW);
  Serial.println("Camera Triggered"); 
} 


//Server Endpoints

void handleRoot() {
  
  String currentIntervalMsg= "Interval set to"+String(triggerInterval)+ " seconds";
  server.send(200, "text/html", HTML_HEADER+"<div class=\"time\">"+currentIntervalMsg +"<div>"+ HTML_FORM+HTML_FOOTER);

}

void handleNotFound() {
  
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  
}

void setInterval(){
    Serial.println("setInterval");
    triggerInterval= String(server.arg("interval")).toFloat();
    Serial.println("TriggerInterval (Seconds): ");
    Serial.println(triggerInterval);
     
  triggerTimer.deleteTimer(triggerTimerId);
  
  triggerTimerId = triggerTimer.setInterval(triggerInterval*1000, triggerCamera);

  triggerTimer.restartTimer(triggerTimerId);
  
  String response = " Interval Set for "+ String(triggerInterval*1000)+ " Seconds";
  Serial.println(response);
  server.send(200, "text/plain", response);
    
}
