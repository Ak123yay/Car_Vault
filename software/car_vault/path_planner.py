import heapq
from typing import Dict, List, Optional, Tuple

GridPoint = Tuple[int, int]


def heuristic(a: GridPoint, b: GridPoint) -> float:
    return abs(a[0] - b[0]) + abs(a[1] - b[1])


class AStarPlanner:
    def __init__(self, obstacle_value: int = 255):
        self.obstacle_value = obstacle_value

    def neighbors(self, grid, node: GridPoint):
        x, y = node
        for nx, ny in [(x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1)]:
            if 0 <= ny < grid.shape[0] and 0 <= nx < grid.shape[1]:
                if grid[ny, nx] != self.obstacle_value:
                    yield nx, ny

    def plan(self, grid, start: GridPoint, goal: GridPoint) -> List[GridPoint]:
        frontier: list[tuple[float, GridPoint]] = []
        heapq.heappush(frontier, (0.0, start))
        came_from: Dict[GridPoint, Optional[GridPoint]] = {start: None}
        cost_so_far: Dict[GridPoint, float] = {start: 0.0}
        while frontier:
            _, current = heapq.heappop(frontier)
            if current == goal:
                break
            for nxt in self.neighbors(grid, current):
                new_cost = cost_so_far[current] + 1.0
                if nxt not in cost_so_far or new_cost < cost_so_far[nxt]:
                    cost_so_far[nxt] = new_cost
                    priority = new_cost + heuristic(nxt, goal)
                    heapq.heappush(frontier, (priority, nxt))
                    came_from[nxt] = current
        if goal not in came_from:
            return []
        path = []
        cur: Optional[GridPoint] = goal
        while cur is not None:
            path.append(cur)
            cur = came_from[cur]
        path.reverse()
        return path
