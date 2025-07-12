#include <driver/ledc.h>

const int threshold = 3;
const int PWM_CHANNEL = 0;    // ESP32 has 16 channels which can generate 16 independent waveforms
const int PWM_FREQ = 1000;     // Recall that Arduino Uno is ~490 Hz. Official ESP32 example uses 5,000Hz
const int PWM_RESOLUTION = 8; // We'll use same resolution as Uno (8 bits, 0-255) but ESP32 can go up to 16 bits
const int MAX_DUTY_CYCLE = (int)(pow(2, PWM_RESOLUTION) - 1); 
const int dutyCycle = 0.5 * MAX_DUTY_CYCLE;

void setup() {
  Serial.begin(9600);
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  ledcAttach(25, PWM_FREQ, PWM_RESOLUTION);
}

void loop() {
  ledcWrite(25, dutyCycle);
  int sensorvalue = analogRead(39);
  float voltage = sensorvalue * 3.3 / 4095.0; 
  Serial.print("Sensor Value: ");
  Serial.print(sensorvalue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage, 3); 
  delay(10);
  if (voltage >= 0.7) {
    digitalWrite(26, HIGH);
  }
  else {
    digitalWrite(26, LOW);
  }
}
