from dataclasses import dataclass


@dataclass
class RobotConfig:
    serial_port: str = "/dev/ttyACM0"
    baudrate: int = 115200
    camera_index: int = 0
    grid_width: int = 80
    grid_height: int = 80
    grid_resolution_m: float = 0.05
    control_rate_hz: float = 10.0
