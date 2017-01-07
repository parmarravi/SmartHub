#include <ESP8266WiFi.h>

const char* ssid = "parmars547";
const char* password = "03122107";
const int ledPin = 0;
WiFiServer server(80);

void printWiFiStatus();

void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  // Configure GPIO2 as OUTPUT.
  pinMode(ledPin, OUTPUT);

  // Start TCP server.
  server.begin();
}

void loop(void) {
  // Check if module is still connected to WiFi.
 String action; 
  if (WiFi.status() != WL_CONNECTED) {
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
    }
    // Print the new IP to Serial.
    printWiFiStatus();
  }
  WiFiClient client = server.available();
if(!client){
  return;
}
Serial.println("new client");
while(!client.available()){
  delay(1);
} 
while(Serial.available())
{
String  inputString=Serial.readString();
  Serial.println(inputString);
} 
     // client.find("led=");
   char s = client.read();
   //   Serial.println(s);
    client.flush();
  // Prepare the response this will make sure that
  String a = "HTTP/1.1 200 OK\r\n\n";
  // Send the response to the client
  client.print(a);
  delay(1);
  client.flush();
  Serial.println("Client disconnected.");
 
  }
void printWiFiStatus() {
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


