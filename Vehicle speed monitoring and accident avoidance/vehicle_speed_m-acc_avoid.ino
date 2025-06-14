#define trigPin 9
#define echoPin 10
#define ledPin 6

long duration;
float distance;
float speed;
float prevDistance = 0;
unsigned long prevTime = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // This Triggers the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Then to Read echo pulse duration
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  //to calculate Speed we use the follows
  unsigned long currentTime = millis();
  float timeDiff = (currentTime - prevTime) / 1000.0;

  if (timeDiff > 0) {
    speed = abs(distance - prevDistance) / timeDiff;
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm\tSpeed: ");
  Serial.print(speed);
  Serial.println(" cm/s");

  // Decision logic
  if (distance < 15 && speed > 50) {
    digitalWrite(ledPin, HIGH);
    Serial.println("⚠️ ALERT: Motion Detected! Speed HIGH & Distance LOW!");
    Serial.println("⚠️ Accident MAY Occur! LED ON");
  } else if (distance < 15) {
    digitalWrite(ledPin, HIGH);
    Serial.println("⚠️ Motion Detected! Object very close.");
    Serial.println("⚠️ Risk of Collision! LED ON");
  } else if (speed > 50) {
    digitalWrite(ledPin, HIGH);
    Serial.println("⚠️ Speeding Detected!");
    Serial.println("⚠️ Accident Risk due to speed. LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("✅ Safe: Normal Conditions. LED OFF");
  }

  prevDistance = distance;
  prevTime = currentTime;
  
  delay(500);  // Adjust based on desired update rate
}
