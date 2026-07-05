# Demo Plan

## Final Demo Goal

The final demo should show a small indoor robot using a camera, IMU, wheel encoders, mapping, path planning, and PID control to move toward a target point.

```text
Camera + IMU + Encoders
        |
        v
Pose Estimation / Odometry
        |
        v
Mapping
        |
        v
A* Path Planning
        |
        v
PID Motor Control
        |
        v
Autonomous Movement
```

## Demo Milestones

### Milestone 1: Safe Motor Test

The robot spins both motors at low speed using the DRV8833 and a separate motor battery rail.

Success condition: both motors spin forward and backward without resetting the Raspberry Pi or ESP32-S3.

### Milestone 2: Encoder Test

The ESP32-S3 reads encoder ticks from both N20 motors.

Success condition: left and right encoder counts go up when the wheels turn.

### Milestone 3: IMU Test

The robot reads the MPU6050 and checks that the gyro/orientation data is usable.

Success condition: IMU data stays mostly stable when the robot is still and changes when the robot is rotated.

### Milestone 4: Camera Test

The Raspberry Pi 5 captures frames from the USB camera.

Success condition: the Pi displays or records live USB camera frames with a known resolution and FPS.

### Milestone 5: Straight-Line PID Test

The robot drives forward using encoder feedback to keep both wheels moving evenly.

Success condition: the robot drives straight over a short indoor distance with limited drift.

### Milestone 6: 90-Degree Turn Test

The robot turns about 90 degrees using IMU and/or encoder feedback.

Success condition: the robot turns close to 90 degrees and stops without overshooting too much.

### Milestone 7: Mapping Test

The robot uses camera and odometry data to start estimating its position and building a simple indoor map.

Success condition: the robot produces a basic map or pose estimate from an indoor test path.

### Milestone 8: A* Path Planning Test

The robot plans a route on a simple occupancy grid.

Success condition: A* makes a valid path from a start point to a goal point while avoiding blocked cells.

### Milestone 9: Autonomous Navigation Test

The robot uses the planned path to drive toward a target point.

Success condition: the robot follows a planned route toward a goal using PID-controlled movement.

## Safety Behavior

The robot should stop if:

- SLAM tracking is lost.
- Encoder readings become invalid.
- IMU readings drift too far.
- Motor commands get stale.
- A stop command is sent.
- An obstacle or unsafe condition is detected.

## Final Video Checklist

The final video should show:

1. The hardware layout.
2. The wiring and split-power setup.
3. The motors and encoders working.
4. The IMU and camera working.
5. The robot driving with PID feedback.
6. A simple map or path-planning output.
7. The robot moving toward a target point.
