# A* Search Algorithm

Simple program that finds the most optimal path from a start point to a given goal.

The A* algorithm finds a path from the start node to the end node by checking for open neighbors of the current node, computing a heuristic for each of the neighbors, and adding those neighbors to the list of open nodes to explore next. The next node to explore is the one with the lowest total cost + heuristic (g + h). This process is repeated until the end is found, as long as there are still open nodes to explore.

## Get Started

Officially supports Windows 10/11 with Visual Studio 2022 and Linux based systems, I don't know about MacOS.

### Windows

1. Clone recursively: `git clone --recursive https://github.com/1neskk/AStarSearch`
2. Run `scripts/setup.bat`
3. Open the solution file and hit F5

### Linux
1. Clone recursively: `git clone --recursive https://github.com/1neskk/AStarSearch`
2. Go to `src` on your terminal
3. Compile the `main.cpp` file
