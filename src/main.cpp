#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Hardware pin definitions (Session 2 wiring)
#define POT_PIN 4   // Potentiometer middle leg (analog input)
#define LED_PIN 40  // External LED + resistor (PWM output)

Adafruit_MPU6050 mpu;

// Tilt switch threshold on the Z-axis (m/s^2):
// Flat/facing up is ~ +9.8 m/s^2; sideways is ~ 0; upside down is ~ -9.8.
// Above 6.0 counts as "tilted up" -> LED enabled.
const float TILT_THRESHOLD = 6.0;

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // Initialize I2C bus on SDA = GPIO8, SCL = GPIO9
  Wire.begin(8, 9);
  if (!mpu.begin()) {
    Serial.println("MPU-6050 not found! Check wiring.");
    while (1) {
      delay(10);
    }
  }
  Serial.println("Tilt switches LED, knob dims brightness.");
}

void loop() {
  // 1. Read potentiometer (0..4095) and scale to PWM duty cycle (0..255)
  int raw = analogRead(POT_PIN);
  int duty = raw / 16;
  if (duty > 255) duty = 255;

  // 2. Read MPU-6050 accelerometer (m/s^2)
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  // 3. Tilt switch logic: enable dimming only when Z-axis points up
  int applied_duty = 0;
  if (a.acceleration.z > TILT_THRESHOLD) {
    applied_duty = duty; // Tilted up -> knob controls LED brightness
  } else {
    applied_duty = 0;    // Tilted sideways or down -> LED stays OFF
  }

  analogWrite(LED_PIN, applied_duty);

  // Print live values for verification
  Serial.printf("Z: %.2f | raw: %d | duty: %d\n",
                a.acceleration.z, raw, applied_duty);

  delay(50);
}
