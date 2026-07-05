
# Car Vault: Indoor Mapping Robot

Car Vault is a small indoor robot I am building so it can map a room and drive to a target point. It uses a Raspberry Pi 5, ESP32-S3, USB camera, MPU6050 IMU, and two N20 motors with encoders.

![System diagram](assets/system-diagram.png)

## Project Summary

This is not meant to be a simple remote-control car. The goal is to build a real robot system where the parts work together.

The Raspberry Pi 5 does the bigger thinking jobs, like camera processing, SLAM tests, mapping, path planning, and deciding where the robot should go. The ESP32-S3 handles the faster low-level jobs, like reading the wheel encoders, running PID motor control, sending PWM to the motor driver, stopping the motors if something goes wrong, and sending debug data back to the Pi.

Basic system flow:

```text
USB Camera + MPU6050 IMU + Wheel Encoders
                    |
                    v
            SLAM / Odometry
                    |
                    v
            Occupancy Grid Map
                    |
                    v
              A* Path Planning
                    |
                    v
              PID Motor Control
                    |
                    v
              N20 Encoder Motors
```

## Why I Am Building This

I am building Car Vault because I want to learn how real autonomous robots are put together. A lot of beginner robot cars only use remote control or basic obstacle sensors. This project goes further because it connects sensing, mapping, planning, and motor feedback in one robot.

This project uses:

- Camera-based SLAM and indoor mapping
- IMU heading/orientation data
- Wheel encoder odometry
- Differential-drive movement
- A* path planning
- PID motor control
- Separate power for the Pi and motors
- Logic-level protection for 3.3V GPIO
- 3D-printed chassis parts
- Sensor testing and calibration

## Finished Goal

The finished robot should be able to:

1. Drive indoors using two powered N20 encoder motors.
2. Read wheel encoder data for distance and wheel speed.
3. Read IMU data to help with heading correction.
4. Use a USB camera on the Raspberry Pi 5 for SLAM experiments.
5. Estimate its pose as `(x, y, theta)`.
6. Build a basic indoor map.
7. Plan a route to a goal using A*.
8. Drive toward the goal using PID motor control.
9. Stop safely if tracking, sensor data, or motor commands become unsafe.

## Hardware Plan

### Raspberry Pi 5

The Raspberry Pi 5 handles:

- USB camera capture
- SLAM experiments
- Mapping
- Occupancy grid generation
- A* path planning
- High-level navigation commands
- Future YOLO object detection using the Raspberry Pi AI HAT+ 26 TOPS / Hailo-8

### ESP32-S3

The ESP32-S3 handles:

- Left and right encoder reading
- Motor PWM output
- Motor direction control
- Wheel-speed PID control
- Safety stop behavior
- Telemetry/debug output
- USB serial communication with the Raspberry Pi 5

### Sensors

The robot uses:

- USB camera for visual input
- MPU6050 IMU for orientation and gyro data
- Wheel encoders for odometry and wheel-speed feedback

### Drivetrain

The drivetrain uses:

- Two powered 6V N20 encoder motors
- Two D-hole rubber wheels
- One custom 3D-printed front skid/support
- DRV8833 dual H-bridge motor driver
- A motor power rail that is separate from the Raspberry Pi power rail

## Power And Wiring Safety

The robot uses separate power rails:

- Raspberry Pi 5: stable 5V USB-C power source
- Motors: separate 6V-class motor battery rail
- ESP32-S3: powered from USB or a regulated 5V input, depending on the board setup
- Motor battery positive must never connect to Raspberry Pi 5V or ESP32-S3 3.3V
- Signal grounds must share a common reference when signals go between boards

Because the ESP32-S3 uses 3.3V GPIO, encoder signals must go through a logic-level shifter unless I measure them and confirm they are 3.3V-safe.

![Wiring diagram](assets/wiring-diagram.png)

## CAD / 3D-Printed Parts

The base plate and front support are custom 3D-printed parts. I am not asking for acrylic sheet or a ball caster because I can print these parts.

Included CAD files:

- `cad/chassis_base.stl` - printable base plate model
- `cad/front_skid.stl` - printable passive front skid/support model

![Chassis sketch](assets/chassis-sketch.png)

## Software Plan

Planned software layout:

```text
camera/
  Captures USB camera frames for SLAM.

sensors/
  Reads IMU and encoder/telemetry data.

slam/
  Uses camera, IMU, and odometry data for pose estimation.

mapping/
  Converts pose and environment data into an occupancy grid.

planning/
  Runs A* path planning on the occupancy grid.

control/
  Converts waypoints into movement commands.

firmware/
  ESP32-S3 code for encoders, motor PWM, PID, and safety stop.
```

## Development Plan

### Phase 1: Hardware Bring-Up

- 3D print the chassis/base and front skid
- Mount the N20 motors
- Mount the camera
- Wire the DRV8833 motor driver
- Wire encoder channels through the logic-level shifter unless they test as safe
- Check the separate power rails
- Test motors at low speed
- Test encoders
- Test the MPU6050
- Test the USB camera
- Record real measurements

### Phase 2: Calibration

- Measure wheel diameter
- Measure wheelbase
- Record encoder ticks per revolution
- Calculate centimeters per encoder tick
- Calibrate IMU gyro bias
- Record camera resolution, FPS, height, and tilt

### Phase 3: Motion Control

- Implement motor mixing
- Implement wheel-speed PID
- Test straight-line movement
- Test 90-degree turns
- Add speed limits and safety-stop behavior

### Phase 4: Mapping And Planning

- Run camera-based SLAM experiments
- Estimate robot pose
- Build a basic occupancy map
- Run A* on the map
- Output waypoints

### Phase 5: Autonomous Navigation Demo

- Choose a simple indoor goal
- Build or load a small map
- Plan a path to the goal
- Drive toward the goal using PID control
- Stop safely if tracking or sensors fail

## What I Need Funding For

I already own some major parts and I will 3D print the chassis/base and front support myself. I need funding for the drivetrain, controller, motor driver, power parts, mounting parts, and protection electronics so I can build the robot safely.

Funding will help buy:

- N20 6V encoder motors
- DRV8833 motor driver
- ESP32-S3 development board
- Logic-level shifter
- Motor mounting brackets
- Motor battery holder and AA cells
- Standoffs/fasteners
- Correct D-hole N20 wheels
- Raspberry Pi 5 mobile UPS/battery parts

Estimated requested funding subtotal in `BOM.csv`: **$151.59**.

## Demo Plan

The final demo will show:

1. The hardware layout and 3D-printed chassis.
2. The separate Pi and motor power wiring.
3. The motors and encoders working.
4. The IMU and USB camera working.
5. The robot driving with PID feedback.
6. A simple map or path-planning output.
7. The robot moving toward a target point.

## Current Status

The project is in the hardware design and parts-request stage. The system plan, BOM, diagrams, and CAD/STL files are included. Final measurements, calibration values, pin assignments, and PID constants will be filled in after the parts arrive and the robot is assembled.
=======

