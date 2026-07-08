from .robot_state import Pose2D, EncoderReading


class SlamFrontend:
    """prototype slam front end.

    real version will connect camera features, imu readings, and wheel odometry into a visual-inertial / odometry pipeline.
    this keeps the software architecture clear.
    """

    def __init__(self):
        self.pose = Pose2D()
        self._last_encoders: EncoderReading | None = None

    def update(self, frame, imu_sample, encoders: EncoderReading, detections) -> Pose2D:
        if self._last_encoders is None:
            self._last_encoders = encoders
            return self.pose
        dl = encoders.left_ticks - self._last_encoders.left_ticks
        dr = encoders.right_ticks - self._last_encoders.right_ticks
        self._last_encoders = encoders
        forward = (dl + dr) * 0.0005
        turn = (dr - dl) * 0.0002
        self.pose.x += forward
        self.pose.theta += turn
        return self.pose
