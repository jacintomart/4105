Project 1: A* Search Algorithm

The problem you will be solving is an agent finding a path from one position to a different 
position in a grid. Each position in the grid is represented by a numeric value indicating 
the cost to move to that position from any neighbor. For example,


1 5 2 4 1 5 0 0 4 0
1 5 0 2 4 1 0 2 5 0
1 0 5 5 1 2 1 4 4 3
2 1 2 2 0 0 2 4 4 0
2 0 4 2 0 0 1 5 1 2
0 3 4 1 3 0 4 2 1 3
1 0 3 5 2 5 1 0 4 3
2 4 0 1 0 2 4 2 4 0
0 4 5 5 2 5 3 1 4 3
3 0 3 3 5 5 3 4 1 1


The top-left cell’s value of 1 means that moving TO that cell FROM any of its neighbors has a 
step cost of 1. The cell to the right of it would require a step cost of 5 to move to it from 
any of its neighbors.

A value of 0 indicates that the location cannot be traversed. The agent can move in the four 
cardinal directions one position at a time. The agent cannot move diagonally.


A* Search
Implement the A* algorithm to solve this problem. A list of requirements is below:
- Load the grid from a text file.
- Allow for different start and goal pairs.
- After running the algorithm to solve the grid, display the final path on the grid visually and 
  write the new grid to a separate file.
- Use an admissible heuristic!

Record and print to console:
- The number of expanded nodes when running an algorithm
- The path cost of the solution


How to Compile:
g++ A*_Tester.cpp -o A*

How to Run:
./A*
