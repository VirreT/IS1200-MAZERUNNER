# IS1200-MAZERUNNER

A program that shows and compares BFS, DFS and Dijkstras on a labyrinth. 
The program is run through the boards different switches and a button and the
graphics is shown through VGA.

# HOW TO BUILD AND RUN THE PROGRAM

You will need RISC-V-toolchain, and dtekv-run needs to be installed

Open a terminal and navigate to the projects root directory, where Makefile is located.

Build the program: "make"

Load and start the program on a DTEK-V-board: dtekv-run main.bin

# IF YOU DO NOT HAVE THE BOARD

You can run the emulator "https://dtekv.fritiof.dev/"
choose "Load File" -> main.bin

# SETTINGS

SW0 is the right most switch. Below is a table with different switch combinations

#       ALGORITHMS:
SW1 SW0     00      BFS
SW1 SW0     01      DFS
SW1 SW0     10      Dijkstra
SW1 SW0     11      ALL: runs and compares all three

#       SIZE Of MAZE:
SW3 SW2     00      8 x 8
SW3 SW2     01      16 x 16
SW3 SW2     10      32 x 32
SW3 SW2     11      64 x 64

#         WALLS:
SW4        1/0      On/Off

#         OTHER:
SW5         0       Keep current labyrinth
SW5       1 + Btn   Make a new labyrinth 
BTN     if pressed  Execute the settings and run

After the switches has been modified, wait a short while before executing with BTN.

If size- and wall settings has been modified, a new maze generates even if SW5 is off.

# COMPARING ALGORITHMS ON THE SAME MAZE 

1. Choose the maze size using SW3 and SW2
2. Choose wheter you want walls or not, using SW4
3. Set SW5 to ON and press BTN to generate a maze.
   Repeat until you have a maze you want to use.
4. Set SW5 to OFF to keep that maze.
5. Select an algorithm using SW1 and SW0.
6. Wait a second, then press BTN to run it.
7. To test another algorithm, repeat steps 5 and 6.
   Keep SW5 OFF and leave the size and wall settings unchanged.

ALL runs all three algorithms on the same maze within one run.

# RESULTS
STEPS:  The number of moves along the final path

COST:   The sum of node weights along the final path.
        Regular nodes have weights from 1 - 20.
        The start and goal has no weight, i.e. cost is 0.

BFS - Finds the path with the fewest steps.

DFS - Finds the path without guaranteeing the fewest steps or the lowest cost.

Dijkstra - Finds a path with the lowest cost.

ALL displays a comparison table:
S = STEPS
C = COST

NO PATH - menas that the goal cannot be reached.

# STRUCTURE
src/Main.c:         main loop, algorithm selection, result collection.
src/IO/:            switch and button input.
src/graphics/:      pixels, text, instructions and displaying results.
src/maze/:          node weights, neighbour connections, walls, goal and start.
src/pathfinder/:    BFS, DFS and Dijkstra.
include/:           project header files.

# AUTHORS
Oscar Jernemalm & Victor Tylus