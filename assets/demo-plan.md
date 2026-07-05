# Demo Plan

## Final Demo Goal

The final demo should show the robot using its camera, IMU, wheel encoders, map, path planner, and PID motor control to move toward a target point.

```text
Camera + IMU + Encoders
        |
        v
Position Estimate
        |
        v
Map
        |
        v
A* Path
        |
        v
PID Motor Control
        |
        v
Robot Moves
```

## Demo Milestones

### Milestone 1: Safe Motor Test

The robot spins both motors slowly using the DRV8833 and the separate motor battery.

Success condition: both motors spin forward and backward without resetting the Raspberry Pi or ESP32-S3.

### Milestone 2: Encoder Test

The ESP32-S3 reads encoder ticks from both N20 motors.

Success condition: left and right encoder counts go up when the wheels turn.

### Milestone 3: IMU Test

The robot reads the MPU6050.

Success condition: the IMU values stay mostly still when the robot is not moving, and they change when I rotate the robot.

### Milestone 4: Camera Test

The Raspberry Pi 5 gets frames from the USB camera.

Success condition: the Pi shows or records live camera frames with a known resolution and FPS.

### Milestone 5: Straight-Line PID Test

The robot drives forward and uses encoder feedback to keep the wheels moving evenly.

Success condition: the robot drives straight for a short indoor distance without drifting too much.

### Milestone 6: 90-Degree Turn Test

The robot turns about 90 degrees using IMU and/or encoder feedback.

Success condition: the robot turns close to 90 degrees and stops without overshooting too much.

### Milestone 7: Mapping Test

The robot uses camera and wheel data to start estimating where it is and making a simple map.

Success condition: the robot produces a basic map or position estimate from an indoor test path.

### Milestone 8: A* Path Planning Test

The robot plans a route on a simple grid map.

Success condition: A* makes a path from the start to the goal while avoiding blocked spaces.

### Milestone 9: Autonomous Navigation Test

The robot uses the planned path to drive toward a target point.

Success condition: the robot follows the path toward the goal using PID-controlled movement.

## Safety Behavior

The robot should stop if:

- SLAM tracking is lost.
- Encoder readings stop making sense.
- IMU readings drift too much.
- Motor commands get stale.
- A stop command is sent.
- An obstacle or unsafe condition is detected.

## Final Video Checklist

The final video should show:

1. The robot layout.
2. The split-power wiring.
3. The motors and encoders working.
4. The IMU and camera working.
5. The robot driving with PID feedback.
6. A simple map or path-planning output.
7. The robot moving toward a target point.
