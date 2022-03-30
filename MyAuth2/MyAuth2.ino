#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h> 
#include <ESP8266HTTPClient.h> // for http request to Google API
/* --- HTML FILE --- */
#include "index.h"
#include "login.h"
#include "admin.h"
//#include "404.h"

// 4x1 keypad
const uint8_t Key1 = D1;
const uint8_t Key2 = D2;
const uint8_t Key3 = D3;
const uint8_t Key4 = D4;

const int buttonPin[4] = {Key1 , Key2 ,Key3 ,Key4 };

// light 
const uint8_t GreenPin = D7;
const uint8_t RedPin = D6;

// Wifi setting 
const char SSID[] = "Taylor";
const char WIFIpassword[] = "Hh033229232";

// Admin user setting 
const char USERNAME[] = "admin";
const char PASSWORD[] = "admin";

// Door password
String DoorPassword= "123";
uint8_t DoorPasswordLen = 3;
uint8_t idx = 0 ;
bool Open = false ; 

// google app script API
String AppURL = "https://script.google.com/macros/s/AKfycbyxtctWmkk0tgnCqc30kakWwgKVrshhzud1ivoZd80_vvK9XSHyFCT6AbScogiOfLHAOA/exec";

// open 8080 port 
ESP8266WebServer server(8080);

// get current press key 
char GetKey(){
    for(uint8_t i=0 ; i<4 ; i++){
    byte btn_state = digitalRead( buttonPin[i] ) ;

    if( btn_state == LOW ){
        switch(buttonPin[i]){
            case Key1: 
                return '1';
            case Key2:
                return '2';
            case Key3:
                return '3';
            case Key4:
                return '4'; 
        }
    }
  }
  return '0';
}

// check door state
void Check(bool flag){
    if(flag){ // green light
        digitalWrite(RedPin, LOW);
        digitalWrite(GreenPin, HIGH);
    }
    else{
        digitalWrite(RedPin, HIGH);
        digitalWrite(GreenPin, LOW);
    }
}
// reset door
void ResetDoor(){
    idx=0;
    Open = false;
    Check(false);
}

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
    if( server.hasArg("PASSWORD") ){
        DoorPassword = server.arg("PASSWORD");
        DoorPasswordLen = DoorPassword.length();
        Serial.print("New password : ");
        Serial.println(DoorPassword);
        Serial.println("update door password");
        // server.sendHeader("Location","/admin");
    }

    server.send(200,"text/html",ADMIN_HTML);
}

void HandleLogout(){
    Serial.println("Disconnection");
    server.sendHeader("Location","/");
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


void UpdateRecord(){
    if(WiFi.status()!= WL_CONNECTED){
      Serial.println("Bad connection!");
      return ;
    }
    Serial.println("update Record");
    WiFiClient client;
    HTTPClient http;
    http.begin(client,AppURL.c_str() );
    // send request
    int httpResponseCode = http.GET();

    if ( httpResponseCode>0 ) {
        Serial.println("Update Record successfully");
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
    }
    else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
}

void setup(){
    /*---- hardware setup ----*/
    // keypad 
    pinMode(Key1, INPUT_PULLUP);
    pinMode(Key2, INPUT_PULLUP);
    pinMode(Key3, INPUT_PULLUP);
    pinMode(Key4, INPUT_PULLUP);
    // light 
    pinMode(GreenPin, OUTPUT);
    pinMode(RedPin, OUTPUT);
    // init light state
    Check(false);

    /*---- software setup----*/
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
    // start server 
    server.begin();
    Serial.println("HTTP server started");
}

void loop(void){
    char key = GetKey();

    if( key != '0'){
        Serial.println(key);
    }
    if(key == '4'){
        ResetDoor();
    }
    if(key == DoorPassword[idx] ) idx++;
    // password correct 
    if( idx == DoorPasswordLen ){ 
        Check(true);
        //  first time open door
        if( !Open ){ 
            UpdateRecord();
            Open = true;
        }
    }

    server.handleClient();
    delay(500);
}
