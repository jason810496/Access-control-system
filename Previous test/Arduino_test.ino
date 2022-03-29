//#include <Keypad.h>
#include <Keypad.h>            //涵入程式庫 Keypad.h

char* pwd = "1234";       //設定密碼字元

int pwd_len = 4;
int idx = 0;
const byte ROWS_size = 4;
const byte COLS_size = 4;
char keys[ROWS][COLS] = {      //定義 4*4 keypad 矩陣
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};

byte rowPins[ROWS_size] = { 9, 8, 7, 6 };         //4*4 keypad 連接 Arduino 方式
byte colPins[COLS_size] = { 5, 4, 3, 2 };
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
const int RedPin = 12;                          //紅色 LED 連接 Arduino pin 12
const int GreenPin = 13;                      //綠色 LED 連接 Arduino pin 13

void setup(){
    pinMode(RedPin, OUTPUT);
    pinMode(GreenPin, OUTPUT);
    Serial.begin(9600);

    Check(true);
}

void loop(){
    char key = keypad.getKey();

    Serial.println(key) ;

    if (key == '*' || key == '#'){
        idx = 0;
        Check(true);
    }
    if (key == pwd[idx] ){
        idx ++;
    }
    if (idx == pwd_len ){
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