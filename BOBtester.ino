int passIndicatorPin = 13;
int failIndicatorPin = 12;
int repeatPin = 10;
int pins[26] = {22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47};
//int pins[17] = {2,3,4,5,6,7,8,9,10,11,12,14,15,16,17,18,19};
 
void setup() {
  Serial.begin(9600);
  
  pinMode(passIndicatorPin, OUTPUT);
  digitalWrite(passIndicatorPin, LOW);

  pinMode(failIndicatorPin, OUTPUT);
  digitalWrite(failIndicatorPin, LOW);

}

void loop() {
  int result = 0;
  
  for(int f = 0; f < 26; f++) {
    Serial.println(pins[f]);

    result |= test(pins[f]);
  }
  
  if(result == 0) {
    pass();
  }
}

void pass() {
  Serial.println("You earned a cookie!");
  
  // Lock into infinite loop 
  pinMode(repeatPin, INPUT_PULLUP);
  digitalWrite(passIndicatorPin, HIGH);
  delay(1000);
  digitalWrite(passIndicatorPin, LOW);
}

void fail(int pin) {
  Serial.print("Pin test failed!");
  Serial.print(pin, DEC);
  Serial.print('\n');
  
  // Lock into infinite loop 
  pinMode(repeatPin, INPUT_PULLUP);
  digitalWrite(failIndicatorPin, HIGH);
  delay(1000);
  digitalWrite(failIndicatorPin, LOW);
}

// The Following function sets OutPut pin as HIGH Then cycles through the rest of the pins and checks there is and input
// If an input is found test is failed
int test(int outputPin){
  for(int i = 0; i < 26 ; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }

  //delay( 500 );
  
  pinMode(outputPin, OUTPUT);
  digitalWrite(outputPin, LOW);

  //delay( 500 );
    
  for(int i = 0; i < 26 ; i++) {
    if(pins[i] == outputPin) {
      continue;
    }
    
    int pinState = digitalRead(pins[i]);
    if(pinState == LOW) {
      fail(pins[i]);
      return 1;
    }  
  }
  
  return 0;
}
