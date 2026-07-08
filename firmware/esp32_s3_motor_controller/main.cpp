#include <Arduino.h>

constexpr int LEFT_PWM_PIN = -1;
constexpr int LEFT_DIR_PIN = -1;
constexpr int RIGHT_PWM_PIN = -1;
constexpr int RIGHT_DIR_PIN = -1;

constexpr int LEFT_ENC_A_PIN = -1;
constexpr int LEFT_ENC_B_PIN = -1;
constexpr int RIGHT_ENC_A_PIN = -1;
constexpr int RIGHT_ENC_B_PIN = -1;

constexpr int PWM_MAX = 255;
constexpr unsigned long COMMAND_TIMEOUT_MS = 500;
constexpr unsigned long CONTROL_PERIOD_MS = 20;

volatile long left_ticks = 0;
volatile long right_ticks = 0;
long last_left_ticks = 0;
long last_right_ticks = 0;

float target_left = 0.0f;
float target_right = 0.0f;
unsigned long last_command_ms = 0;
unsigned long last_control_ms = 0;

struct PIDState {
  float kp = 0.9f;
  float ki = 0.0f;
  float kd = 0.05f;
  float integral = 0.0f;
  float last_error = 0.0f;
};

PIDState left_pid;
PIDState right_pid;

void IRAM_ATTR onLeftEncoderA() {
  if (LEFT_ENC_B_PIN < 0) {
    left_ticks++;
    return;
  }
  bool b = digitalRead(LEFT_ENC_B_PIN);
  left_ticks += b ? -1 : 1;
}

void IRAM_ATTR onRightEncoderA() {
  if (RIGHT_ENC_B_PIN < 0) {
    right_ticks++;
    return;
  }
  bool b = digitalRead(RIGHT_ENC_B_PIN);
  right_ticks += b ? 1 : -1;
}

void writeMotor(int pwm_pin, int dir_pin, float effort) {
  effort = constrain(effort, -1.0f, 1.0f);
  int pwm = (int)(fabs(effort) * PWM_MAX);

  if (dir_pin >= 0) {
    digitalWrite(dir_pin, effort >= 0.0f ? HIGH : LOW);
  }
  if (pwm_pin >= 0) {
    analogWrite(pwm_pin, pwm);
  }
}

void stopMotors() {
  target_left = 0.0f;
  target_right = 0.0f;
  writeMotor(LEFT_PWM_PIN, LEFT_DIR_PIN, 0.0f);
  writeMotor(RIGHT_PWM_PIN, RIGHT_DIR_PIN, 0.0f);
}

float pidStep(PIDState &pid, float target, float measured, float dt) {
  float error = target - measured;
  pid.integral += error * dt;
  pid.integral = constrain(pid.integral, -1.0f, 1.0f);
  float derivative = (error - pid.last_error) / max(dt, 0.001f);
  pid.last_error = error;
  return pid.kp * error + pid.ki * pid.integral + pid.kd * derivative;
}

void runControlLoop() {
  unsigned long now = millis();
  if (now - last_control_ms < CONTROL_PERIOD_MS) return;

  float dt = (now - last_control_ms) / 1000.0f;
  last_control_ms = now;

  noInterrupts();
  long l_ticks = left_ticks;
  long r_ticks = right_ticks;
  interrupts();

  long dl = l_ticks - last_left_ticks;
  long dr = r_ticks - last_right_ticks;
  last_left_ticks = l_ticks;
  last_right_ticks = r_ticks;

  // prototype normalized wheel velocity estimate.
  // real version will convert ticks/sec using exact encoder ticks per revolution and wheel diameter.
  float measured_left = constrain((float)dl / 20.0f, -1.0f, 1.0f);
  float measured_right = constrain((float)dr / 20.0f, -1.0f, 1.0f);

  float left_effort = pidStep(left_pid, target_left, measured_left, dt);
  float right_effort = pidStep(right_pid, target_right, measured_right, dt);

  writeMotor(LEFT_PWM_PIN, LEFT_DIR_PIN, left_effort);
  writeMotor(RIGHT_PWM_PIN, RIGHT_DIR_PIN, right_effort);
}

void printStatus() {
  Serial.print("status target_left=");
  Serial.print(target_left, 3);
  Serial.print(" target_right=");
  Serial.print(target_right, 3);
  Serial.print(" left_ticks=");
  Serial.print(left_ticks);
  Serial.print(" right_ticks=");
  Serial.println(right_ticks);
}

void handleCommand(String cmd) {
  cmd.trim();
  cmd.toLowerCase();
  last_command_ms = millis();

  if (cmd == "ping") {
    Serial.println("pong");
  } else if (cmd == "stop") {
    stopMotors();
    Serial.println("ok stop");
  } else if (cmd == "get_encoders") {
    Serial.print("enc ");
    Serial.print(left_ticks);
    Serial.print(" ");
    Serial.println(right_ticks);
  } else if (cmd == "reset_encoders") {
    noInterrupts();
    left_ticks = 0;
    right_ticks = 0;
    interrupts();
    last_left_ticks = 0;
    last_right_ticks = 0;
    Serial.println("ok reset_encoders");
  } else if (cmd == "get_status") {
    printStatus();
  } else if (cmd.startsWith("drive ")) {
    int first_space = cmd.indexOf(' ');
    int second_space = cmd.indexOf(' ', first_space + 1);
    if (second_space < 0) {
      Serial.println("err drive needs left and right values");
      return;
    }
    float l = cmd.substring(first_space + 1, second_space).toFloat();
    float r = cmd.substring(second_space + 1).toFloat();
    target_left = constrain(l, -1.0f, 1.0f);
    target_right = constrain(r, -1.0f, 1.0f);
    Serial.println("ok drive");
  } else {
    Serial.println("err unknown_command");
  }
}

void setup() {
  Serial.begin(115200);
  delay(200);

  if (LEFT_DIR_PIN >= 0) pinMode(LEFT_DIR_PIN, OUTPUT);
  if (RIGHT_DIR_PIN >= 0) pinMode(RIGHT_DIR_PIN, OUTPUT);
  if (LEFT_PWM_PIN >= 0) pinMode(LEFT_PWM_PIN, OUTPUT);
  if (RIGHT_PWM_PIN >= 0) pinMode(RIGHT_PWM_PIN, OUTPUT);
  if (LEFT_ENC_A_PIN >= 0) pinMode(LEFT_ENC_A_PIN, INPUT_PULLUP);
  if (LEFT_ENC_B_PIN >= 0) pinMode(LEFT_ENC_B_PIN, INPUT_PULLUP);
  if (RIGHT_ENC_A_PIN >= 0) pinMode(RIGHT_ENC_A_PIN, INPUT_PULLUP);
  if (RIGHT_ENC_B_PIN >= 0) pinMode(RIGHT_ENC_B_PIN, INPUT_PULLUP);

  if (LEFT_ENC_A_PIN >= 0) attachInterrupt(digitalPinToInterrupt(LEFT_ENC_A_PIN), onLeftEncoderA, CHANGE);
  if (RIGHT_ENC_A_PIN >= 0) attachInterrupt(digitalPinToInterrupt(RIGHT_ENC_A_PIN), onRightEncoderA, CHANGE);

  last_command_ms = millis();
  last_control_ms = millis();
  stopMotors();
  Serial.println("car_vault_esp32s3_ready");
}

void loop() {
  while (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    handleCommand(cmd);
  }
  if (millis() - last_command_ms > COMMAND_TIMEOUT_MS) stopMotors();
  runControlLoop();
}
