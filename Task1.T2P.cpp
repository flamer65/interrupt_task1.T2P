const int trigPin = 9;
const int echoPin = 10;
const int motionSensorPin = 5;
const int ledPin = 13;

volatile bool motionDetected = false; // volatile variable to indicate motion detection

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motionSensorPin, INPUT_PULLUP); // enable the internal pull-up resistor
  pinMode(ledPin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(motionSensorPin), motionDetectedISR, RISING); // attach interrupt on the rising edge of the motion sensor pin
}

void loop() {
  if (motionDetected) { // if motion is detected
    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH); // turn on the LED
    delay(500); // wait for 500 milliseconds
    digitalWrite(ledPin, LOW); // turn off the LED
    motionDetected = false; // reset the motion detection flag
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}

void motionDetectedISR() {
  motionDetected = true; // set the motion detection flag
}
