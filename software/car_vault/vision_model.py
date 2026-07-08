from dataclasses import dataclass
from typing import List, Tuple


@dataclass
class Detection:
    label: str
    confidence: float
    bbox_xyxy: Tuple[int, int, int, int]


class VisionModel:
    """prototype object/obstacle vision model wrapper.

    later this can load a yolo model on the raspberry pi ai hat / hailo runtime.
    for now it returns simple placeholder detections so the software structure is clear.
    """

    def __init__(self, model_path: str | None = None, simulate: bool = False):
        self.model_path = model_path
        self.simulate = simulate

    def infer(self, frame) -> List[Detection]:
        if frame is None:
            return []
        if self.simulate:
            return [Detection("possible_obstacle", 0.50, (120, 90, 200, 180))]
        return []
