import argparse
import time

try:
    import cv2
except ImportError:
    cv2 = None

from .config import RobotConfig
from .occupancy_grid import OccupancyGrid
from .path_planner import AStarPlanner
from .robot_state import EncoderReading
from .serial_link import MotorControllerLink
from .slam_frontend import SlamFrontend
from .vision_model import VisionModel


def open_camera(index: int, simulate: bool):
    if simulate or cv2 is None:
        return None
    cap = cv2.VideoCapture(index)
    if not cap.isOpened():
        return None
    return cap


def main():
    parser = argparse.ArgumentParser(description="car vault raspberry pi prototype")
    parser.add_argument("--simulate", action="store_true", help="run without robot hardware")
    parser.add_argument("--serial", default="/dev/ttyACM0", help="esp32-s3 serial port")
    parser.add_argument("--camera", type=int, default=0, help="camera index")
    parser.add_argument("--steps", type=int, default=50, help="prototype loop steps")
    args = parser.parse_args()

    cfg = RobotConfig(serial_port=args.serial, camera_index=args.camera)
    link = MotorControllerLink(cfg.serial_port, cfg.baudrate, simulate=args.simulate)
    status = link.connect()
    print(f"motor link: {status}")

    camera = open_camera(cfg.camera_index, args.simulate)
    vision = VisionModel(simulate=args.simulate)
    slam = SlamFrontend()
    grid = OccupancyGrid(cfg.grid_width, cfg.grid_height, cfg.grid_resolution_m)
    planner = AStarPlanner()
    goal = (cfg.grid_width // 2 + 12, cfg.grid_height // 2)

    try:
        for step in range(args.steps):
            if camera is not None:
                ok, frame = camera.read()
                if not ok:
                    frame = None
            else:
                frame = None
            detections = vision.infer(frame)
            enc = link.get_encoders() or (0, 0)
            pose = slam.update(frame, imu_sample=None, encoders=EncoderReading(*enc), detections=detections)
            grid.mark_robot_seen_area(pose)
            grid.mark_detections_as_obstacles(pose, detections)
            start = grid.world_to_grid(pose.x, pose.y)
            path = planner.plan(grid.grid, start, goal)
            if path:
                link.drive(0.25, 0.25)
            else:
                link.stop()
            print(f"step={step} pose=({pose.x:.2f},{pose.y:.2f},{pose.theta:.2f}) detections={len(detections)} path_len={len(path)}")
            time.sleep(1.0 / cfg.control_rate_hz)
    finally:
        link.stop()
        if camera is not None:
            camera.release()


if __name__ == "__main__":
    main()
