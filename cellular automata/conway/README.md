# Conway's Game Of Life

## about
Conway's Game of Life is a cellular automata designed by the mathematican, Conway.
It has three basic rules for determining the survival of a cell
    - 1. A Living cell will die if it has more than 3 neigbouring live cells
    - 2. A Living cell will die if it has less than 2 neighbouring live cells
    - 3. A dead cell will become alive if it has more than 3 neighbouring live cells

These three very basic principles give a simplistic yet fascinating view of a population.

## Noteworthy implementation details

In this implementation specifically, I've made use of three pointers to do the 
switching back and forth of the grid. Which has greatly contributed to the performance 
of the simulation.

```cpp
bool** game;  /// the grid which is displayed
bool** after; /// the grid which is updated
bool** temp;  /// the grid which is placeholding
```

This lets us prevent the monotonous copying of the arrays over with a loop
