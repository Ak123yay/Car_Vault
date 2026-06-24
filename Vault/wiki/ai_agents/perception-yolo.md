# Future YOLO Perception

## Purpose

Define the boundary for adding YOLO later without destabilizing the base navigation stack.

YOLO is future work. It should not be implemented until camera capture, SLAM, occupancy mapping, A*, PID, and failure handling pass baseline validation.

Owned accelerator:

- Raspberry Pi AI HAT+ 26 TOPS.
- Hailo-8 inference accelerator.
- Runs YOLO/object detection locally on the Pi 5 from the USB camera stream.

Boundary:

- Hailo-8 accelerates neural-network inference only.
- ORB-SLAM3 remains the SLAM/localization layer.
- Arduino Uno remains the encoder/PID/motor-control layer.

## Intended Role

YOLO can provide object labels that affect behavior, such as:

- Person detected.
- Chair or obstacle detected.
- Doorway detected.
- Stop-relevant object detected.

## Integration Options

Option 1: Modify occupancy grid.

- YOLO detections become obstacle or semantic cells.
- Useful for persistent objects.
- Requires camera-to-world projection.

Option 2: Trigger stop/replan behavior.

- YOLO detections become immediate safety signals.
- Easier first integration.
- Does not require full semantic mapping.

Recommended first approach:

```text
USB camera -> Pi 5 -> Hailo-8 YOLO inference -> detection -> failure manager stop/replan signal
```

## Requirements Before YOLO

- Stable camera frame pipeline.
- Raspberry Pi AI HAT+ 26 TOPS software installed and detected.
- Working Hailo YOLO demo on the Pi 5 camera stream.
- Valid pose estimate.
- Working A* path planning.
- Working PID waypoint following.
- Defined sudden-obstacle behavior in `wiki/operations/failure-handling.md`.

## Out Of Scope For Now

- Semantic SLAM.
- Object permanence.
- Object tracking across frames.
- Training custom models.
