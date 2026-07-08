import numpy as np
from .robot_state import Pose2D


class OccupancyGrid:
    def __init__(self, width: int, height: int, resolution_m: float):
        self.width = width
        self.height = height
        self.resolution_m = resolution_m
        self.grid = np.zeros((height, width), dtype=np.uint8)

    def world_to_grid(self, x: float, y: float):
        gx = int(self.width / 2 + x / self.resolution_m)
        gy = int(self.height / 2 - y / self.resolution_m)
        return gx, gy

    def mark_robot_seen_area(self, pose: Pose2D) -> None:
        gx, gy = self.world_to_grid(pose.x, pose.y)
        if 0 <= gx < self.width and 0 <= gy < self.height:
            self.grid[gy, gx] = 1

    def mark_detections_as_obstacles(self, pose: Pose2D, detections) -> None:
        if not detections:
            return
        gx, gy = self.world_to_grid(pose.x + 0.3, pose.y)
        for dy in range(-1, 2):
            for dx in range(-1, 2):
                x = gx + dx
                y = gy + dy
                if 0 <= x < self.width and 0 <= y < self.height:
                    self.grid[y, x] = 255
