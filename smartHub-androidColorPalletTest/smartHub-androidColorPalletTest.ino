#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

#define PIN            2   // NodeMCU Input Pin
#define NUMPIXELS      16    // Number of Pixels on the Ring

//wifi settings
const char ssid[] = "parmars547"; 
const char password[] = "03122107";
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  while (!Serial) ; // Needed for Leonardo only
  delay(250);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  pixels.begin();
  pixels.show();
  for(uint8_t i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(0xff,0x00,0x00));
    }
    
    pixels.show(); // This sends the updated pixel color to the hardware.

  delay(500);
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start TCP server.
  server.begin();
  Serial.println("Server started");
 

}

void loop() 
{

 WiFiClient client = server.available();

if(!client)
{
  return;
}

Serial.println("new client");

while(!client.available())
{
  delay(1);
} 
     String line = client.readStringUntil('\r');
     Serial.println(line);
     Colorsep(line);
     client.flush();
     delay(10);
  // Prepare the response this will make sure that
  String a = "HTTP/1.1 200 OK\r\n\n";

  // Send the response to the client
  client.print(a);
  delay(1);
  client.flush();
  Serial.println("Client disconnected.");

  }
  

void Colorsep(String colorTxt)
{
  String colour = colorTxt.substring(10,18);
  String value = colour;
  Serial.println(value);
  String brit = value.substring(0,2);    //seperate out the number ff2012ff
  String red = value.substring(2,4);    
  String green =value.substring(4,6);  
  String blue = value.substring(6,8); 
  
 int brightness=hexToDec(brit);
  int  redcolor=hexToDec(red);
     int greencolor=hexToDec(green);
       int bluecolor=hexToDec(blue);
 
 pixels.setBrightness(brightness);
    for(int i=0; i<NUMPIXELS; i++) 
    {
      pixels.setPixelColor(i, pixels.Color(redcolor,greencolor,bluecolor));
      pixels.show();
    }

 }
 
 unsigned int hexToDec(String hexString)
{
  
  unsigned int decValue = 0;
  int nextInt;

  for (int i = 0; i < hexString.length(); i++) {
    
    nextInt = int(hexString.charAt(i));
    Serial.println(nextInt);
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    
    decValue = (decValue * 16) + nextInt;
  }
  
  return decValue;
}

      



