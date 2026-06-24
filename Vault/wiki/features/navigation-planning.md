# Navigation & Planning

## Purpose

Define how the robot plans movement from its current pose to a goal.

## Inputs

| Input | Source |
| --- | --- |
| Current pose `(x, y, theta)` | SLAM or fallback odometry |
| Occupancy grid | Mapping layer |
| Goal pose or goal cell | User command or higher-level behavior |
| Robot footprint | Hardware design |

## Occupancy Grid

Each grid cell should represent a fixed-size area of the floor.

Required fields:

```text
cell = {
  x_index,
  y_index,
  state,
  cost
}
```

Allowed states:

- `free`
- `occupied`
- `unknown`

Initial example costs:

```text
Obstacle cost = 100
Free space = 1
Unknown space = 50
```

These values are placeholders and should be tuned after mapping tests.

## A* Rules

Planner requirements:

- Use the current pose as the start.
- Use the requested goal cell as the target.
- Reject occupied cells.
- Penalize unknown cells.
- Prefer shorter paths when costs are equal.
- Return failure if no valid path exists.

Neighbor model:

- Start with 4-connected movement for simplicity.
- Consider 8-connected movement only after collision clearance is defined.

Heuristic:

- Manhattan distance for 4-connected grids.
- Euclidean or octile distance for 8-connected grids.

## Waypoint Output

A* returns grid cells. Control should receive simplified waypoints.

```text
waypoint = {
  x_m,
  y_m,
  desired_theta_rad,
  tolerance_m
}
```

The waypoint layer should remove unnecessary intermediate points only after basic path following works.

## Replanning Conditions

Replan when:

- The goal changes.
- The current path becomes blocked.
- Pose jumps or relocalizes.
- The robot deviates too far from the planned path.
- Failure handling requests a replan.

## Open Decisions

- Grid resolution.
- Robot footprint clearance.
- Unknown-space policy.
- Whether YOLO detections modify the grid later or trigger stop/replan separately.
