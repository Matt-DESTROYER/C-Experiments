# C Pathfindr

A simple implementation of a grid-based path-finding algorithm written in C.

## The Algorithm
The algorithm is very simple, yet effective;
1. Start from the target position.
2. Explore the immediately surrounding cells that can be moved to (above, below, and either side).
3. When each cell is explored, assign it a direction, pointing to the previous tile.
4. Repeat this until each cell has been explored (in which case there is no path) or the start position is reached.

> Note: Even 

To follow the path, simply follow those directions to the end.

