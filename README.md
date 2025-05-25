# Rock, Paper, Scissors Cellular Automata
A command-line program written in C that simulates a cellular automaton with rules based on Rock, Paper, Scissors. 

- Each cell in a grid can be in one of 3 states - representing **Rock, Paper, or Scissors** (represented in code as 0, 1, and 2 respectively).
- Cells consider their 8 immediate neighbors (Moore neighborhood).
- Like RPS, each state is 'weak' to another state and 'strong' against another.
- If a cell's neighbours have enough cells that it is 'weak'against (determined by the THRESHOLD and RANDOM_THRESHOLD_MODIFIER values), it will be 'conquered' into that state.
- This ruleset creates spiral waves of repeating captures.

## Global Parameters
There are 5 global parameters that can be tinkered at the top of *rps.c* to change the behaviour of the automata. They are as follows:

**GRIDXSIZE** - The number of cells horizontally on the grid.

**GRIDYSIZE** - The number of cells vertically on the grid.

**THRESHOLD** - The number of neighbours that need to be 'strong' against a given cell for it to become 'conquered'.

**RANDOM_THRESHOLD_MODIFIER** - Before evaluating if a cell changes state, a number between 0 and this parameter will be generated and added to the threshold for each cell for each step. Setting this parameter to a non-zero value will make the CA stochastic. 

**SET_SEED** - Set to -1 by default to use a random seed. Set to any other integer to set your own seed.

## Sample Settings

At threshold sums around 4 - like with 3 THRESHOLD and 1 RANDOM / 2 THRESHOLD and 2 RANDOM, you observe the spiral wave behaviour.

---
![3-1](https://github.com/user-attachments/assets/8a219f99-c280-4e59-8343-d0ce605668e7)

---
At low threshold sums like 2, you observe cells rapidly flickering between the 3 states. (Not shown due to concerns with flashing images)


At high threshold values with no RANDOM, you observe cells crystallizing immediately into equilibrium within a few generations.

---
![4-0](https://github.com/user-attachments/assets/974cbfe3-91a9-4ee6-b077-3ce908391ec7)



---
An old project retooled for a university assignment.
