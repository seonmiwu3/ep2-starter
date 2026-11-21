/*
 * Session 1 — blink a plain LED (the homework, on real hardware).
 * --------------------------------------------------------------------------
 * The blink in src/main.cpp uses the board's addressable RGB LED, which you
 * send a COLOUR to. This one uses an ordinary LED from your box, which you
 * switch ON and OFF. It is the same idea with simpler hardware — and it is
 * the same sketch you ran in the simulator.
 *
 * WIRING (power off while you wire):
 *   GPIO40 -> resistor (220-330 ohm) -> LED long leg (anode)
 *   LED short leg (cathode) -> GND
 *
 *   THE RESISTOR IS NOT OPTIONAL. Straight across a pin, an LED draws more
 *   current than the pin should give. 220 ohm is bright, 330 is comfortable,
 *   1k works but is dim. Long leg = positive.
 *
 * WHY GPIO40: it's free on this board, it's not a strapping pin (avoid
 * GPIO0/3/45/46), and it's clear of the I2C bus (8/9), the session-1 scope
 * signal (GPIO2) and the octal flash/PSRAM pins (33-37). Session 2's homework
 * reuses the same pin, so you can leave the LED where it is.
 *
 * THE HOMEWORK: make this blink YOURS. A rhythm, a pattern, morse code, a
 * heartbeat — something you designed. Then push it as `FINAL: my blink`.
 */
#include <Arduino.h>

/*
 * Session 1 — Custom Blink: International Morse Code SOS (... --- ...)
 * --------------------------------------------------------------------------
 * Wiring: GPIO40 -> 220-330 ohm resistor -> LED long leg (+) -> short leg (-) -> GND
 *
 * Morse code timing rules used here (1 unit = 200 ms):
 *   - Dot (.)          = 1 unit  (200 ms ON)
 *   - Dash (-)         = 3 units (600 ms ON)
 *   - Intra-character  = 1 unit  (200 ms OFF between dots/dashes in a letter)
 *   - Inter-character  = 3 units (500 ms total OFF between letters: 200 ms + 300 ms)
 *   - Word gap         = ~8 units (1700 ms total OFF before repeating SOS)
 */

#include <Arduino.h>

#define LED_PIN 40  // External plain LED connected to GPIO40

void setup() {
  Serial.begin(115200);
  delay(300);
  pinMode(LED_PIN, OUTPUT);  // Configure GPIO40 as a digital output
  Serial.println();
  Serial.println("SOS Morse code blinking on GPIO40.");
}

// Helper function: flashes the LED ON for 'duration' ms, then OFF for 1 unit (200 ms)
void blink(int duration) {
  digitalWrite(LED_PIN, HIGH);  // Turn LED ON
  delay(duration);              // Keep LED ON (200 ms for dot, 600 ms for dash)
  digitalWrite(LED_PIN, LOW);   // Turn LED OFF
  delay(200);                   // Standard 1-unit pause between flashes in the same letter
}

void loop() {
  // W (.--)
  blink(200); blink(600); blink(600);
  delay(300); // Pause between letters

  // E (.)
  blink(200);
  delay(1500); // Pause before repeating WE
}


