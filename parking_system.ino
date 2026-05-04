#include <Ultrasonic.h>

// Define sensor pins
#define TRIG_PIN_1 2
#define ECHO_PIN_1 3
#define TRIG_PIN_2 4
#define ECHO_PIN_2 5
#define TRIG_PIN_3 6
#define ECHO_PIN_3 7

// LED pins for slot status
#define LED_1 8
#define LED_2 9
#define LED_3 10

// Distance threshold (cm)
#define THRESHOLD 10

void setup() {
    Serial.begin(9600);
    pinMode(TRIG_PIN_1, OUTPUT);
    pinMode(ECHO_PIN_1, INPUT);
    pinMode(TRIG_PIN_2, OUTPUT);
    pinMode(ECHO_PIN_2, INPUT);
    pinMode(TRIG_PIN_3, OUTPUT);
    pinMode(ECHO_PIN_3, INPUT);
    pinMode(LED_1, OUTPUT);
    pinMode(LED_2, OUTPUT);
    pinMode(LED_3, OUTPUT);
    Serial.println("Smart Parking System Started");
}

long getDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    return duration * 0.034 / 2;
}

void checkSlot(int trigPin, int echoPin, int ledPin, int slotNum) {
    long distance = getDistance(trigPin, echoPin);
    if (distance < THRESHOLD) {
        digitalWrite(ledPin, HIGH); // Slot occupied
        Serial.print("Slot "); Serial.print(slotNum);
        Serial.println(": OCCUPIED");
    } else {
        digitalWrite(ledPin, LOW); // Slot free
        Serial.print("Slot "); Serial.print(slotNum);
        Serial.println(": FREE");
    }
}

void loop() {
    Serial.println("--- Parking Status ---");
    checkSlot(TRIG_PIN_1, ECHO_PIN_1, LED_1, 1);
    checkSlot(TRIG_PIN_2, ECHO_PIN_2, LED_2, 2);
    checkSlot(TRIG_PIN_3, ECHO_PIN_3, LED_3, 3);
    delay(1000);
}
