# SLAM Configuration

## Purpose

Define the ORB-SLAM3 setup for the Tier 3 robot.

The SLAM layer should produce pose and map information from camera and IMU input. Encoder odometry is used to validate movement scale and support fallback behavior.

## ORB-SLAM3 Inputs

| Input | Source | Requirement |
| --- | --- | --- |
| Image frames | USB camera | Timestamped, calibrated, stable FPS |
| IMU samples | IMU | Timestamped, bias-corrected, configured noise values |
| Camera intrinsics | Calibration | `fx`, `fy`, `cx`, `cy`, distortion |
| Camera-IMU transform | Hardware measurement | Relative pose between camera and IMU |

## Initial Configuration Targets

Example starting values only:

```text
Camera FPS: 30
IMU rate: 200 Hz
Feature points: 1000-2000
```

Do not finalize configuration until camera and IMU calibration are complete.

## Required Config Fields

Camera:

- USB device path or camera index.
- Resolution
- FPS
- Camera model
- Intrinsics
- Distortion coefficients

IMU:

- Accelerometer noise
- Gyroscope noise
- Accelerometer random walk
- Gyroscope random walk
- IMU frequency

Extrinsics:

- Camera-to-IMU translation
- Camera-to-IMU rotation

ORB feature settings:

- Number of features
- Scale factor
- Pyramid levels
- FAST threshold values

## Output Contract

SLAM should output:

```text
pose = {
  x_m,
  y_m,
  theta_rad,
  timestamp_s,
  tracking_state,
  confidence
}
```

Tracking states:

- `tracking`
- `lost`
- `relocalizing`
- `initializing`

## Encoder Relationship

Encoders do not replace SLAM. They provide:

- Short-term distance estimate.
- Motion scale sanity check.
- Fallback dead reckoning when SLAM tracking is lost.
- Mismatch detection when left/right wheels disagree unexpectedly.

## Validation Path

1. Run USB camera-only capture and confirm stable FPS.
2. Run IMU logging and confirm stable sample rate.
3. Run ORB-SLAM3 in a textured indoor area.
4. Compare SLAM movement estimate against encoder odometry.
5. Record drift over a repeatable path.
