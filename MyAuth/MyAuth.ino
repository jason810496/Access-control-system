#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char SSID[] = "Taylor";
const char WIFIpassword[] = "Hh033229232";

const char USERNAME[] = "admin";
const char PASSWORD[] = "NodeMCU==++";

ESP8266WebServer server(80);

//Check if header is present and correct
bool is_authentified(){

  if (server.hasHeader("Cookie")){
    // Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    // Serial.println(cookie);

    // if cookie == "ESPSESSIONID=1"
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("Authentification Successful");
      return true;
    }
  }
  Serial.println("Authentification Failed");
  return false;
}

//login page, also called for disconnect

void handleLogin(){
  String msg;

  

  if (server.hasHeader("Cookie")){
    Serial.print("Found cookie: ");
    String cookie = server.header("Cookie");
    Serial.println(cookie);

    // is authentified 
    if (cookie.indexOf("ESPSESSIONID=1") != -1) {
      Serial.println("is authed & go to login page");

      server.sendHeader("Location","/");
      server.send(301);

      Serial.println("redirect to main page");
      return ;
    }
  }


  if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){
    if (server.arg("USERNAME") == "admin" &&  server.arg("PASSWORD") == "admin" ){
      server.sendHeader("Location","/");
      server.sendHeader("Cache-Control","no-cache");
      server.sendHeader("Set-Cookie","ESPSESSIONID=1");
      server.send(301);
      Serial.println("Log in Successful");
      return;
    }
  msg = "Wrong username/password! try again.";
  Serial.println("Log in Failed");
  }
  String content = "<html><body><form action='/login' method='POST'>To log in, please use : admin/admin<br>";
  content += "User:<input type='text' name='USERNAME' placeholder='user name'><br>";
  content += "Password:<input type='password' name='PASSWORD' placeholder='password'><br>";
  content += "<input type='submit' name='SUBMIT' value='Submit'></form>" + msg + "<br>";
  content += "You also can go <a href='/inline'>here</a></body></html>";
  server.send(200, "text/html", content);
}

//root page can be accessed only if authentification is ok
void handleRoot(){
  Serial.println("Enter handleRoot");
  String header;
  if (!is_authentified()){
    server.sendHeader("Location","/login");
    server.sendHeader("Cache-Control","no-cache");
    server.send(301);
    return;
  }
  String content = "<html><body><H2>hello, you successfully connected to esp8266!</H2><br>";
  if (server.hasHeader("User-Agent")){
    content += "the user agent used is : " + server.header("User-Agent") + "<br><br>";
  }
  content += "You can access this page until you <a href=\"/login?DISCONNECT=YES\">disconnect</a></body></html>";
  server.send(200, "text/html", content);
}

/*---- Handle function ----*/
void HandleAdmin(){
    Serial.println("Handle Admin");
    // check permission
    if( !is_authentified() ){
        server.sendHeader("Location","/login");
        server.sendHeader("Cache-Control","no-cache");
        server.send(301);
        return;
    }

    server.send(200,"text/html",ADMIN_HTML);
}

void HandleRoot(){

}

void HandleLogin(){

    // check password
    if (server.hasArg("USERNAME") && server.hasArg("PASSWORD")){
        if (server.arg("USERNAME") == USERNAME &&  server.arg("PASSWORD") == PASSWORD ){
        server.sendHeader("Location","/");
        server.sendHeader("Cache-Control","no-cache");
        server.sendHeader("Set-Cookie","ESPSESSIONID=1");
        server.send(301);
        Serial.println("Log in Successful");
        return;
        }
    }
}

void HandleLogout(){
    Serial.println("Disconnection");
    server.sendHeader("Location","/login");
    server.sendHeader("Cache-Control","no-cache");
    server.sendHeader("Set-Cookie","ESPSESSIONID=0");
    server.send(301);
    return;
}

void HandleNotFound(){

}
/*---- Handle function end ----*/

//no need authentification
void handleNotFound(){
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works without need of authentification");
  });

  server.onNotFound(handleNotFound);
  //here the list of headers to be recorded
  const char * headerkeys[] = {"User-Agent","Cookie"} ;
  size_t headerkeyssize = sizeof(headerkeys)/sizeof(char*);
  //ask server to track these headers
  server.collectHeaders(headerkeys, headerkeyssize );


  server.begin();
  Serial.println("HTTP server started");
}


void setup2(){
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
    serveronNotFound(HandleNotFound);

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
}
