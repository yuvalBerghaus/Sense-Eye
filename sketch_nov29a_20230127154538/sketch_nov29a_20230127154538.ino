#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// Replace with your network credentials
const char* ssid     = "Yuval";
const char* password = "Panama507";
bool pressed = false;
int recommended_index;

// Set web server port number to 80
ESP8266WebServer server(80);
// Host
const char* host = "192.168.14.3";
WiFiClient client_to_server;
// Variable to store the HTTP request
String header;
// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output0State = "off";
String output2State = "off";
// Assign output variables to GPIO pins
const int output5 = 5; // HP
const int output4 = 4;    //GPIO4
const int output0 = 0;    //GPIO0
const int output2 = 2;    //GPIO2
const char input13 = 13; // the button GPIO16
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
String url;


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
  pinMode(output5, OUTPUT);
  pinMode(output4, OUTPUT);
  pinMode(output0, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(input13, INPUT_PULLUP);
  // Set outputs to LOW
  digitalWrite(output5, LOW);
  digitalWrite(output4, LOW);
  digitalWrite(output0, LOW);
  digitalWrite(output2, LOW);
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }




  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


///////////////////////////////////////////////////////////////
    delay(5000);
  Serial.print("connecting to ");
  Serial.println(host);
    // Use WiFiClient class to create TCP connections

  const int httpPort = 5000;
  // Connect to server
  if (client_to_server.connect(host, httpPort)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection to server failed");
  }
 // We now create a URI for the request
  url = "/save_id?color_band=red&ip="+WiFi.localIP().toString();
  // Send request
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client_to_server.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
client_to_server.stop();
///////////////////////////////////////////////////////////////////////////////

  delay(100);
  
  server.on("/recommend/5", handle_5);
  server.on("/recommend/4", handle_4);
  server.on("/recommend/0", handle_0);
  server.on("/recommend/2", handle_2);
  server.begin();
}

void loop(){
  server.handleClient();
  bool currentState = digitalRead(input13);
  if(currentState == pressed) {
    Serial.println("Hello");
    turn_recommended_buzzer();
    while(digitalRead(input13) == pressed) {
      // Do nothing
    }
  }
}


void handle_5() {
    // output5State = "on";
    recommended_index = 5;
    server.send(200, "text/html", "hello from esp8266!"); 
    // digitalWrite(output5, HIGH);
    // delay(1000);
    // output5State = "off";
    // digitalWrite(output5, LOW);
}

void handle_4() {
    recommended_index = 4;
    server.send(200, "text/html", "hello from esp8266!"); 
    // output4State = "on";
    // digitalWrite(output4, HIGH);
    // delay(1000);
    // output5State = "off";
    // digitalWrite(output4, LOW);
}
void handle_0() {
    recommended_index = 0;
    server.send(200, "text/html", "hello from esp8266!"); 
    // output0State = "on";
    // digitalWrite(output0, HIGH);
    // delay(1000);
    // output5State = "off";
    // digitalWrite(output0, LOW);
}

void handle_2() {
    recommended_index = 2;
    server.send(200, "text/html", "hello from esp8266!"); 
    // output2State = "on";
    // digitalWrite(output2, HIGH);
    // delay(1000);
    // output2State = "off";
    // digitalWrite(output2, LOW);
}

void turn_recommended_buzzer() {
  digitalWrite(recommended_index, HIGH);
  delay(1000);
  digitalWrite(recommended_index, LOW);
  
}