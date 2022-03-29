#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

/* --- HTML FILE --- */
#include "index.h"
#include "login.h"
#include "admin.h"
//#include "404.h"

// Wifi setting 
const char SSID[] = "Taylor";
const char WIFIpassword[] = "Hh033229232";

// Admin user setting 
const char USERNAME[] = "admin";
const char PASSWORD[] = "admin";

// Door password
String DoorPassword= "123123";
uint8_t DoorPasswordLen = 6;

ESP8266WebServer server(8080);

//Check if header is present and correct
bool is_authentified(){

  if (server.hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);

    // if cookie == "ESPSESSIONID=1"
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

/*---- Handle function ----*/

void HandleRoot(){
    server.send(200,"text/html",INDEX_HTML);
}

void HandleLogin(){

    Serial.println( " to login page");

    if (server.hasHeader("Cookie")){
        Serial.print("Found cookie: ");
        String cookie = server.header("Cookie");
        Serial.println(cookie);

        // is authentified 
        if (cookie.indexOf("ESPSESSIONID=1") != -1) {
            Serial.println("is authed & go to login page");

            server.sendHeader("Location","/admin");
            server.send(301);

            Serial.println("redirect to admin page");
            return ;
        }
    }

    Serial.println(" Login Check point ");
    // check password
    if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){

        // debug 
        Serial.println( server.arg("USERNAME"));
        Serial.println( server.arg("PASSWORD"));
        if (server.arg("USERNAME") == USERNAME &&  server.arg("PASSWORD") == PASSWORD ){
        server.sendHeader("Location","/admin");
        server.sendHeader("Cache-Control","no-cache");
        server.sendHeader("Set-Cookie","ESPSESSIONID=1");
        server.send(301);
        Serial.println("Log in Successful");
        return;
        }
    }

    server.send(200,"text/html", String(LOGIN_HTML));
}

void HandleAdmin(){
    Serial.println("Handle Admin");
    // check permission
    if( !is_authentified() ){
        server.sendHeader("Location","/login");
        server.sendHeader("Cache-Control","no-cache");
        server.send(301);
        return;
    }

    // update Door password
    if( server.hasArd("PASSWORD") ){
        DoorPassword = server.arg("PASSWORD");
        DoorPasswordLen = DoorPassword.length();
        Serial.print("New password : ");
        Serial.print(DoorPassword);
        Serial.println("update door password");
    }

    server.send(200,"text/html",ADMIN_HTML);
}

void HandleLogout(){
    Serial.println("Disconnection");
    server.sendHeader("Location","/login");
    server.sendHeader("Cache-Control","no-cache");
    server.sendHeader("Set-Cookie","ESPSESSIONID=0");
    server.send(301);
    return;

    server.send(301, "text/plain", "Logout...");
}

void HandleNotFound(){
    server.send(404, "text/plain", "error 404");
}
/*---- Handle function end ----*/

void setup(){
    // init Serial 
    Serial.begin(9600);
    // start connect to AP
    WiFi.begin( SSID , WIFIpassword );

    // Wait for connection 

    while( WiFi.status() != WL_CONNECTED ){
        delay(500);
        Serial.print(".");
    }
    // after connection 
    Serial.println("Connected to WiFi !");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    // routing
    server.on("/" , HandleRoot);
    server.on("/login", HandleLogin);
    server.on("/logout", HandleLogout);
    server.on("/admin", HandleAdmin);
    // handle 404
    server.onNotFound(HandleNotFound);

    //list of headers to be recorded
    const char * headerkeys[] = {"User-Agent","Cookie"} ;
    size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
    //ask server to track these headers
    server.collectHeaders(headerkeys, headerkeyssize );
    server.begin();
    Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();

  delay(500);
}
