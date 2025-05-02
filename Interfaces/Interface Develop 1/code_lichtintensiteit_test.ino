int intensiteits_pin = A0; // Verander de variabelenaam voor duidelijkheid

void setup() {
    pinMode(intensiteits_pin, INPUT); // INPUT_PUPLUP is niet nodig voor een potentiometer
    Serial.begin(9600);
}

void loop() {
    int intensiteits_waarde = analogRead(intensiteits_pin); // Lees de analoge waarde correct uit
    Serial.print("intensiteit||");
    Serial.println(intensiteits_waarde);
    delay(500);
}

