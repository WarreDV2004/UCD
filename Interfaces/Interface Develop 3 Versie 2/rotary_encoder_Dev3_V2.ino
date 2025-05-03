 int pinA = 3; // Connected to CLK
 int pinB = 4; // Connected to DT
 int drukknop = 5; // Conect to SW
 int encoderPosCount = 0;
 int pinALast;
 int aVal;
 int druk_teller = 0;
 int staat1;
 bool drukknop_last = HIGH;
 unsigned long lastDebounceTime = 0;
 unsigned long debounceDelay = 100;  // 100 ms debounce tijd
 unsigned long lastTurnTime = 0;
 unsigned long turnDebounceDelay = 100; // 100 ms tussen rotaties

 boolean bCW;

 void setup() {
 pinMode (pinA,INPUT);
 pinMode (pinB,INPUT);
 pinMode (drukknop, INPUT_PULLUP);
 /* Read Pin A
 Whatever state it's in will reflect the last position
 */
 pinALast = digitalRead(pinA);
 drukknop_last = digitalRead(drukknop);
 Serial.begin (9600);
}

void loop() {
    
  bool buttonState = digitalRead(drukknop);

  // Debounce controle
  if (buttonState == LOW && drukknop_last == HIGH) {
      if (millis() - lastDebounceTime > debounceDelay) {
          druk_teller++;  // Verhoog teller bij druk
          Serial.println("Drukken");
          // Serial.println(druk_teller);
          lastDebounceTime = millis(); // Reset debounce timer
      }
  }
    
  drukknop_last = buttonState; // Update vorige status


 aVal = digitalRead(pinA);
  if ((pinALast == HIGH) && (aVal == LOW)) { // Falling edge detectie
    if (millis() - lastTurnTime > turnDebounceDelay) {
     if (digitalRead(pinB) == HIGH) {
        encoderPosCount++;
        bCW = true;
        Serial.println("DraaienR");
      } else {
        encoderPosCount--;
        bCW = false;
        Serial.println("DraaienL");
      }
      lastTurnTime = millis(); // Reset debounce timer voor draai
    }
  }
  pinALast = aVal;
}