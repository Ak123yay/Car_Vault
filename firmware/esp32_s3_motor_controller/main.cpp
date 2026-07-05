// Car Vault ESP32-S3 motor controller bring-up skeleton
// Status: design-stage skeleton, not production firmware.
// Pin assignments will be filled after final wiring review and encoder voltage verification.

#include <Arduino.h>

constexpr int PIN_UNASSIGNED = -1;
constexpr int LEFT_PWM_PIN  = PIN_UNASSIGNED;
constexpr int LEFT_DIR_PIN  = PIN_UNASSIGNED;
constexpr int RIGHT_PWM_PIN = PIN_UNASSIGNED;
constexpr int RIGHT_DIR_PIN = PIN_UNASSIGNED;
constexpr int LEFT_ENC_A_PIN  = PIN_UNASSIGNED;
constexpr int LEFT_ENC_B_PIN  = PIN_UNASSIGNED;
constexpr int RIGHT_ENC_A_PIN = PIN_UNASSIGNED;
constexpr int RIGHT_ENC_B_PIN = PIN_UNASSIGNED;

volatile long left_ticks = 0;
volatile long right_ticks = 0;
unsigned long last_command_ms = 0;
constexpr unsigned long COMMAND_TIMEOUT_MS = 500;

void stopMotors() {
  if (LEFT_PWM_PIN >= 0) {
    analogWrite(LEFT_PWM_PIN, 0);
  }
  if (RIGHT_PWM_PIN >= 0) {
    analogWrite(RIGHT_PWM_PIN, 0);
  }
}

void setup() {
  Serial.begin(115200);
  last_command_ms = millis();
  stopMotors();
  Serial.println("CAR_VAULT_ESP32S3_READY");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    last_command_ms = millis();

    if (cmd == "PING") {
      Serial.println("PONG");
    } else if (cmd == "STOP") {
      stopMotors();
      Serial.println("STOPPED");
    } else if (cmd == "GET_ENCODERS") {
      Serial.print("ENC ");
      Serial.print(left_ticks);
      Serial.print(" ");
      Serial.println(right_ticks);
    } else {
      Serial.println("ERR UNKNOWN_COMMAND");
    }
  }

  if (millis() - last_command_ms > COMMAND_TIMEOUT_MS) {
    stopMotors();
  }
}
