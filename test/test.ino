
/*--- keypad setting part  ---*/
const uint8_t Key1 = D1;
const uint8_t Key2 = D2;
const uint8_t Key3 = D3;
const uint8_t Key4 = D4;

const int buttonPin[4] = {Key1 , Key2 ,Key3 ,Key4 };

/*---  light setting part ---*/

const uint8_t Redpin = D6 ;
const uint8_t Greenpin = D7;
/*---  password setting part ---*/

char Door_password[] = "123123";
uint8_t Door_pwd_len = 6;

uint8_t cur_pwd_idx = 0;

void setup() {
  // put your setup code here, to run once:

    Serial.begin(9600);                  
    Serial.print("Hello World\n");  

    pinMode(Key1, INPUT_PULLUP);// set pin as input
    pinMode(Key2, INPUT_PULLUP);// set pin as input
    pinMode(Key3, INPUT_PULLUP);// set pin as input
    pinMode(Key4, INPUT_PULLUP);// set pin as input

    
    pinMode(D6, OUTPUT);
    pinMode(D7, OUTPUT);
    Door_state(false);

}

char Get_key(){

    for(uint8_t i=0 ; i<4 ; i++){

        if( digitalRead( buttonPin[i] ) == LOW ){

            switch( buttonPin[i] ){
            
                case Key1 :
                    return '1';
                case Key2 :
                    return '2';
                case Key3 :
                    return '3';
                case Key4 :
                    return '4';
            }
        }
    }

    return '0';
}


void Door_state(bool flag){

    if( flag ){
        digitalWrite(Greenpin,HIGH);
        digitalWrite(Redpin,LOW);
    }
    else{
        digitalWrite(Greenpin,LOW);
        digitalWrite(Redpin,HIGH);
    }
}


void loop() {
  
    char key = Get_key();

    Serial.println(key);

    if( key == '4'){
        cur_pwd_idx = 0;
        Door_state(false);
    }
    if( key == Door_password[ cur_pwd_idx ] ){
        cur_pwd_idx ++ ;
    }

    if( cur_pwd_idx == Door_pwd_len){
        Door_state(true);
    }

    delay(300);
}
