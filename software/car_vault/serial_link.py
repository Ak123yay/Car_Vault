import time
from dataclasses import dataclass

try:
    import serial
except ImportError:
    serial = None


@dataclass
class SerialStatus:
    connected: bool
    last_line: str = ""


class MotorControllerLink:
    def __init__(self, port: str, baudrate: int = 115200, simulate: bool = False):
        self.simulate = simulate
        self.port = port
        self.baudrate = baudrate
        self._ser = None
        self._sim_left = 0
        self._sim_right = 0

    def connect(self) -> SerialStatus:
        if self.simulate:
            return SerialStatus(True, "simulation mode")
        if serial is None:
            return SerialStatus(False, "pyserial not installed")
        self._ser = serial.Serial(self.port, self.baudrate, timeout=0.2)
        time.sleep(2.0)
        self.send("ping")
        return SerialStatus(True, self.read_line())

    def send(self, command: str) -> None:
        if self.simulate:
            if command.startswith("drive"):
                self._sim_left += 4
                self._sim_right += 4
            return
        if self._ser is not None:
            self._ser.write((command.strip() + "\n").encode("utf-8"))

    def read_line(self) -> str:
        if self.simulate:
            return "pong"
        if self._ser is None:
            return ""
        return self._ser.readline().decode("utf-8", errors="replace").strip()

    def drive(self, left: float, right: float) -> None:
        left = max(-1.0, min(1.0, left))
        right = max(-1.0, min(1.0, right))
        self.send(f"drive {left:.3f} {right:.3f}")

    def stop(self) -> None:
        self.send("stop")

    def get_encoders(self):
        if self.simulate:
            self._sim_left += 1
            self._sim_right += 1
            return self._sim_left, self._sim_right
        self.send("get_encoders")
        line = self.read_line()
        parts = line.split()
        if len(parts) == 3 and parts[0] == "enc":
            return int(parts[1]), int(parts[2])
        return None
