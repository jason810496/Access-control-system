/*   include Keypad header*/
#include <Keypad.h>            

/*   include ESP8266 header*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SoftwareSerial.h>

/* Door Wifi_pwd setting */
const char* Door_pwd = "1234";       
int Door_pwd_len = 4;
int idx = 0;

/* keypad setting part & light part */
const byte ROWS_size = 4;
const byte COLS_size = 4;
char keys[ROWS_size][COLS_size] = {      
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS_size] = { D9, D8, D7, D6 };        
byte colPins[COLS_size] = { D5, D4, D3, D2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS_size, COLS_size );
const uint8_t RedPin = SD2;                         
const uint8_t GreenPin = SD3;                     


/* ESP2688 setting */

#ifndef STASSID
#define STASSID "Taylor_2"  //無線分享器的名稱
#define STAPSK  "Hh033229232"    //密碼
#endif

const char* ssid = STASSID;
const char* Wifi_pwd = STAPSK;

ESP8266WebServer server(80);

void handleRoot() {  //訪客進入主網頁時顯示的內容
  server.send(200, "text/plain", "Hello From ESP8266 !");
}

void handleNotFound() {  //找不到網頁時顯示的內容
  server.send(404, "text/plain", "File Not Found");
}


void setup(){
    pinMode(RedPin, OUTPUT);
    pinMode(GreenPin, OUTPUT);

    Serial.println("Setup");
    Serial.begin(9600);
    Check(true);

    WiFi.mode(WIFI_STA);
    Serial.println("Begin");
    WiFi.begin(ssid, Wifi_pwd);
    Serial.println("-");

    // 等待WiFi連線
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //在監控視窗顯示取得的IP

    if (MDNS.begin("esp8266")) {
        Serial.println("MDNS responder started");
    }

    server.on("/", handleRoot);  //綁定主網頁會觸發的副程式

    server.onNotFound(handleNotFound);  //綁定找不到網頁時會觸發的副程式

    server.begin();
    Serial.println("HTTP server started");

}

void loop(){
    server.handleClient();
    MDNS.update();

    char key = keypad.getKey();

    Serial.println(key) ;

    if (key == '*' || key == '#'){
        idx = 0;
        Check(true);
    }
    if (key == Door_pwd[idx] ){
        idx ++;
    }
    if (idx == Door_pwd_len ){
        Check(false);
    }
    delay(100);
}

void Check(bool is_locked){
    if ( is_locked ){
        digitalWrite(RedPin, HIGH);
        digitalWrite(GreenPin, LOW);
        //  ServoMotor.write(11);
    }
    else{       //open the door                                    //輸入密碼和預設密碼相符，綠色 LED 亮，開門
        digitalWrite(RedPin, LOW);
        digitalWrite(GreenPin, HIGH);
        //  ServoMotor.write(90);
    }
}