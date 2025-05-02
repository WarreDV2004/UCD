//  Pin-definities
const int pinCLK = 3;       // Rotary encoder CLK (A)
const int pinDT = 4;        // Rotary encoder DT (B)
const int pinButton = 5;    // Drukknop op encoder
const int drukknop2 = 2;    // Tweede drukknop

//  Encoder variabelen
int encoderPos = 0;     
int encoderPosLast = 0;    
int lastCLKState;           
unsigned long lastEncoderTime = 0;  
const unsigned long encoderDebounceDelay = 100; 

//  Drukknop 1 (encoder) variabelen
int buttonPressCount = 0;   
bool lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long buttonDebounceDelay = 200;

//  Drukknop 2 variabelen
bool lastButtonState2 = HIGH;
unsigned long lastDebounceTime2 = 0;
const unsigned long buttonDebounceDelay2 = 200;

//  Nieuw: statusvariabele voor eerste drukknop bij buttonPressCount == 2
int drukknopStatus = 0;

void setup() {
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinButton, INPUT_PULLUP);
    pinMode(drukknop2, INPUT_PULLUP);

    lastCLKState = digitalRead(pinCLK);
    lastButtonState = digitalRead(pinButton);
    lastButtonState2 = digitalRead(drukknop2);

    Serial.begin(9600);
}

void loop() {
    checkEncoder();  
    checkButton();   
    checkButton2();  
}

// 🔹 Controleer de rotary encoder (met debounce)
void checkEncoder() {
    int currentCLKState = digitalRead(pinCLK);

    if (currentCLKState != lastCLKState) {
        if (millis() - lastEncoderTime > encoderDebounceDelay) {
            int tempPos = encoderPos;

            if (digitalRead(pinDT) != currentCLKState) {
                tempPos++;  // Clockwise
            } else {
                tempPos--;  // Counterclockwise
            }

            if (buttonPressCount == 1) {
                if (tempPos >= -3 && tempPos <= 3) {
                    encoderPos = tempPos;
                }
            } else if (buttonPressCount == 4) {
                if (tempPos >= 0 && tempPos <= 16) {
                    encoderPos = tempPos;
                }
            } else if (buttonPressCount == 2) {
                if (tempPos >= 0 && tempPos <= 2) {
                    encoderPos = tempPos;
                } else if (tempPos < 0) {
                    encoderPos = 2;
                } else if (tempPos > 2){
                    encoderPos = 0;
                }
            } else {
                encoderPos = tempPos;
            }

            Serial.print("intensiteit||");
            Serial.println(encoderPos);
            lastEncoderTime = millis();
        }
    }

    lastCLKState = currentCLKState;
}

// 🔹 Controleer de drukknop op de encoder
void checkButton() {
    bool buttonState = digitalRead(pinButton);

    if (buttonState == LOW && lastButtonState == HIGH) {
        if (millis() - lastDebounceTime > buttonDebounceDelay) {
          if (buttonPressCount == 4 || buttonPressCount == 5) {
            buttonPressCount = 2;
          } 
          else {
            buttonPressCount++;
          }
            
            encoderPosLast = encoderPos;
            encoderPos = 0;
            Serial.print("drukken||");
            Serial.println(buttonPressCount);

            if (buttonPressCount == 3) {
                if (encoderPosLast == 0) {
                    buttonPressCount = 1;
                } else if (encoderPosLast == 1) {
                    buttonPressCount = 5;
                } else if (encoderPosLast == 2) {
                    buttonPressCount = 4;
                }
                Serial.print("drukken||");
                Serial.println(buttonPressCount);
            }

            lastDebounceTime = millis();
        }
    }

    lastButtonState = buttonState;
}

// 🔹 Controleer de tweede drukknop
void checkButton2() {
    bool currentButtonState2 = digitalRead(drukknop2);

    if (currentButtonState2 == LOW && lastButtonState2 == HIGH) {
        if (millis() - lastDebounceTime2 > buttonDebounceDelay2) {
            Serial.println("drukken2||1");
            lastDebounceTime2 = millis();
        }
    }

    lastButtonState2 = currentButtonState2;
}
