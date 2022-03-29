#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"
 
ESP8266WebServer server(80);
 
const char* ssid = "Taylor";
const char* password =  "Hh033229232";
 
void setup() {
 
    Serial.begin(9600);
    WiFi.begin(ssid, password);  //Connect to the WiFi network
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    // 192.168.34.102
    Serial.println(WiFi.localIP());  //Print the local IP

     Serial.print("MAC: ");
     Serial.println(WiFi.macAddress());
 
    server.on("/",HandleRoot);
    
    server.on("/body", handleBody); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");
 
}
 
void loop() {
 
    server.handleClient(); //Handling of incoming requests

    delay(500);
}
 
void handleBody() { //Handler for the body path
 
      if (server.hasArg("plain")== false){ //Check if body received

            Serial.println("Client in ");
            
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}

void HandleRoot(){

    Serial.println("client in");

    server.send(200, "text/html", String(INDEX_HTML) );
}
