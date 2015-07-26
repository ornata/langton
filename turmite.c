#include <inttypes.h>
#include <stdio.h>

#define ROWS 300
#define COLS 300

#define NORTH 8
#define EAST 4
#define SOUTH 2
#define WEST 1

/* Prints out the grid in pbm compliant format */
void print_grid(int8_t grid[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}

/* Turns the ant right from its current position. */
int8_t turn_right(int8_t turmite)
{
    if (turmite == NORTH) {
        turmite = EAST;
        return turmite;
    } else if (turmite == EAST) {
        turmite = SOUTH;
        return turmite;
    } else if (turmite == SOUTH) {
        turmite = WEST;
        return turmite;
    } else {
        turmite = NORTH;
        return turmite;
    }
}

/* Turns the ant left from its current position. */
int8_t turn_left(int8_t turmite)
{
    if (turmite == NORTH) {
        turmite = WEST;
        return turmite;
    } else if (turmite == EAST) {
        turmite = NORTH;
        return turmite;
    } else if (turmite == SOUTH) {
        turmite = EAST;
        return turmite;
    } else {
        turmite = SOUTH;
        return turmite;
    }
}

/* Based off the direction of the ant, move forward one unit. */
void update_position(int8_t turmite, uint32_t* active_x, uint32_t* active_y)
{
    if (turmite == NORTH)
        *active_y = (*active_y + 1) % ROWS;
    else if (turmite == EAST)
        *active_x = (*active_x + 1) % COLS;
    else if (turmite == SOUTH)
        *active_y = (*active_y - 1) % ROWS;
    else
        *active_x = (*active_x - 1) % COLS;

    *active_x %= COLS;
    *active_y %= ROWS;
}

/* Moves a turmite following Langton's ants moves. Runs for iter iterations.*/
void langton (int8_t grid[ROWS][COLS], int iter, uint32_t active_x, uint32_t active_y)
{
    int8_t turmite = NORTH;
    while (iter > 0)
    {
        if (grid[active_x][active_y] == 0)
            turmite = turn_left(turmite);
        else
            turmite = turn_right(turmite);
        grid[active_x][active_y] = !(grid[active_x][active_y]);
        update_position(turmite, &active_x, &active_y);
        iter--;
    }
}

int main (void)
{
    int8_t grid[ROWS][COLS];
    int i, j;

    // Initialize to an empty grid.
    // Non-empty grids can give more interesting behaviour.
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            grid[i][j] = 0;

    langton (grid, 15000, ROWS/3, COLS/2);
    printf("P1\n");
    printf("%d %d\n", ROWS, COLS);
    print_grid(grid);
    return 0;
}