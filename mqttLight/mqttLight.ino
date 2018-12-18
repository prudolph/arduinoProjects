
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <Adafruit_NeoPixel.h>

const char *ssid =  "beard_ubt";    // cannot be longer than 32 characters!
const char *pass =  "Northstar1";    //

// Update these with values suitable for your network.
IPAddress server(192, 168, 2, 55);

#define PIN            14
#define NUMPIXELS      44

// How many NeoPixels are attached to the Arduino?
#define BUFFER_SIZE 100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void callback(char* topic, byte* payload, unsigned int length) {

  // handle message arrived
  Serial.print(topic);
  Serial.print(" => ");


    if(payload[0] == 'o' && payload[1] == 'n')
    {
     for(int i=0; i< strip.numPixels(); i++) {
           strip.setPixelColor(i, 255, 245, 150);
    }
    strip.show();
    }
    else
    {
      for(int i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, 0);
      }
      strip.show();
    }

}

WiFiClient wclient;
PubSubClient client(wclient);

void setup() {
  client.setServer(server,1883);
  strip.begin();
     for(int i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, 255,255 , 255);
      }
  strip.setBrightness(75);
  strip.show(); // Initialize all pixels to 'off'
 delay(2000);
     for(int i=0; i< strip.numPixels(); i++) {
        strip.setPixelColor(i, 0,0,0);
      }
 
 strip.show(); // Initialize all pixels to 'off'
 

  // Setup console
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  client.setCallback(callback);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    WiFi.begin(ssid, pass);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
      return;
    Serial.println("WiFi connected");
  }

  if (WiFi.status() == WL_CONNECTED) {
    if (!client.connected()) {
      if (client.connect("MASONJARLIGHT")) {
  client.publish("outTopic","hello world");
  client.subscribe("MASONJARLIGHT");
      }
    }

    if (client.connected())
      client.loop();
  }
}

