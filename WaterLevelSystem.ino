// Ultrasonic Sensor Pins
const int trigPin = 2;
const int echoPin = 3;

// Threshold Distances
const int closeThreshold = 10; // close the tap when the distance is less than 10 cm
const int openThreshold = 60; // open the tap when the distance is greater than 60 cm

// pin for controlling the relay
const int relayPin = 4;

long duration;
int distance;

void setup() { // put your setup code here, to run once:
// initialize serial communication for debugging purposes
Serial.begin(9600);

//set the ultrasonic sensor pins as input/output
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() { // put your main code here, to run repeatedly:
// Trigger the ultrasonic sensor to send a pulse 
digitalWrite(trigPin, LOW);
delay(2000);
digitalWrite(trigPin, HIGH);
delay(9000);
digitalWrite(trigPin, LOW);

// measure the duration of the echo pulse
duration = pulseIn(echoPin, HIGH);

// calculate the distance in centimeters (speed of sound in air is approximately 343meters per second)
distance = duration * 0.0343/2;

// print the distance to the serial monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");

// control the tap based on water level readings
if (distance < closeThreshold){
  // tank is almost full, close the tap
  digitalWrite(relayPin, HIGH); // Deactivate the relay to close the tap
  Serial.println("Closing the tap...");
} else if (distance > openThreshold){
  // tank is half empty, open the tap
  digitalWrite(relayPin, LOW); // Activate the relay to open  the tap
  Serial.println("Opening the tap...");
}

delay(2000);
}
