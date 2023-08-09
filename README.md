# Rush-Hour

Code Cab - Text-Based Maze Navigation Game
Introduction:
"Code Cab" is a text-based maze navigation game where the player controls a taxi represented by '@' symbol. The objective is to navigate through a maze, avoid obstacles represented by 'X' symbols, and reach the passenger represented by '#' symbol in as few steps as possible.

## Classes and Their Roles:
* Graph Class (Graph):

Represents the maze as a graph with nodes and edges.
Helps in pathfinding using Breadth-First Search (BFS) algorithm to find the shortest path between the taxi and the passenger.
Manages maze connections by creating edges between valid cells.

* MazeGame Class (mazegame):
Represents the maze and the player's interactions.
Generates a maze of a given size and places the taxi and passenger in their initial positions.
Provides methods to move the taxi through the maze in different directions (UP, DOWN, LEFT, RIGHT).
Allows undoing a move, tracking steps taken, and checking for collisions with obstacles or passenger.
Computes the player's score based on the number of steps taken and the shortest path.

* Levels Class (Levels):
Contains a method to define the obstacle density of different maze sizes.
Influences the maze complexity by adjusting the density of obstacles in the maze.
* Player Class (player):
Represents a player with their name and score.
Allows comparison of players based on their scores for leaderboard arrangement.
* Gameplay Overview:
The game begins by asking the player's name and providing a brief explanation of the game's rules.

* The player navigates the maze using keyboard inputs (W, A, S, D) to move UP, LEFT, DOWN, and RIGHT, respectively. They can also UNDO a move (U) or QUIT the game (Q).

* The player's goal is to reach the passenger '#' while avoiding obstacles 'X' in as few steps as possible. Lives are given to retry moves, but they decrease when attempting to undo the previous move.

* The player progresses through five stages with increasing maze sizes and complexities.

* After completing each stage, the player's score is calculated based on the number of steps taken compared to the shortest path. The score is used to determine the player's performance.

* The game keeps track of the player's scores and updates a leaderboard. The leaderboard displays the top players with their names and scores.

### Key Concepts:
The game uses a graph-based approach to represent the maze and apply graph algorithms for navigation.
Each maze cell is a node, and valid connections (edges) are established between neighboring cells.
BFS algorithm helps find the shortest path from the taxi to the passenger, considering obstacles.
### Conclusion:
"Code Cab" is a maze navigation game that challenges players to strategize their movements and find the shortest path while avoiding obstacles. The code showcases the implementation of classes, graph-based maze representation, and player scoring. The game offers an engaging experience for players to test their problem-solving skills and compete for the highest scores on the leaderboard.



