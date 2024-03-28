const int lm35Pin = A0; // Declaring LM35 analog pin
const int ledPin = 13;   // Declaring Onboard LED pin

const int belowthreshold = 250; // Setting up Interval for blinking when temperature is below 30°C
const int abovethreshold = 500; // Setting up Interval for blinking when temperature is above 30°C

float temperature = 0.0;
unsigned long previousMillis = 0;
unsigned long elapsedTime = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(lm35Pin);
  temperature = (sensorValue * 5.0 * 100.0) / 1024.0; // Converting sensor value to temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");

  if (temperature < 30) {
    // Temperature is below 30°C
    if (elapsedTime - previousMillis >= belowthreshold) {
      toggleLED(); // Toggle LED state
      previousMillis = elapsedTime;
    }
  } else {
    // Temperature is above or equal to 30°C
    if (elapsedTime - previousMillis >= abovethreshold) {
      toggleLED(); // Toggle LED state
      previousMillis = elapsedTime;
    }
  }

  // Updating elapsed time
  elapsedTime = millis();
}

void toggleLED() {
  digitalWrite(ledPin, !digitalRead(ledPin)); // Toggle LED state
}
