#ifndef GRID_H
#define GRID_H

#include <stdbool.h>

#define GRID_ROWS 20
#define GRID_COLUMNS 10
#define GRID_SIZE GRID_ROWS * GRID_COLUMNS
#define BREAKING_BRICK_FRAMES 13

#define MIN_LEVEL 1
#define MAX_LEVEL 20

#define EMPTY_BLOCK 0
#define BROKEN_BLOCK 8

/* Maintains information for one player's grid. */
struct grid {
  char blocks[GRID_SIZE];
  int level;
  int lines_to_level;
  int lines_cleared;
  int score;
  bool contains_broken_lines;
  int next_shape_index;
  int shape_index;
  int shape_row;
  int shape_col;
  int shape_rotation;
  bool game_over;
  int drop_delay;
  int drop_counter;
  int animation_counter;
  int animation_index;
};

bool grid_init(struct grid *grid, int level);
void grid_update(struct grid *grid);
char grid_get_block_value(struct grid *grid, int row, int col);
void grid_sweep_broken_lines(struct grid *grid);
void grid_move_shape_left(struct grid *grid);
void grid_move_shape_right(struct grid *grid);
bool grid_move_shape_down(struct grid *grid);
void grid_drop_shape(struct grid *grid);
void grid_rotate_shape(struct grid *grid);

#endif /* GRID_H */
