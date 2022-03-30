const uint8_t Key1 = D1;
const uint8_t Key2 = D2;
const uint8_t Key3 = D3;
const uint8_t Key4 = D4;


const int buttonPin[4] = {Key1 , Key2 ,Key3 ,Key4 };

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);                  
  Serial.print("Hello World\n");  

  pinMode(Key1, INPUT_PULLUP);// set pin as input
  pinMode(Key2, INPUT_PULLUP);// set pin as input
  pinMode(Key3, INPUT_PULLUP);// set pin as input
  pinMode(Key4, INPUT_PULLUP);// set pin as input

}

void loop() {
  // put your main code here, to run repeatedly:

  for(uint8_t i=0 ; i<4 ; i++){
    Serial.print(i);
    Serial.print("  : ");
    byte state = digitalRead( buttonPin[i] ) ;
    Serial.println( state );
      
  }

  
  for(uint8_t i=0 ; i<4 ; i++){
    byte btn_state = digitalRead( buttonPin[i] ) ;

    if( btn_state == LOW ){

      if( buttonPin[i]==Key1){
        Serial.println("1");
      }
      else if( buttonPin[i]==Key2){
        Serial.println("2");
      }
      else if( buttonPin[i]==Key3){
        Serial.println("3");
      }
      else if( buttonPin[i]==Key4){
        Serial.println("4");
      }
    }
  }

  delay(500);
}