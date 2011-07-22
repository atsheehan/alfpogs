#include <stdlib.h>
#include "grid.h"
#include "shape.h"

#define POINTS_PER_LINE 10
#define LINES_PER_LEVEL 20
#define TICKS_PER_FRAME 1

#define NO_ACTIVE_SHAPE -1
#define BASE_DROP_DELAY 5
#define DELAY_INCREMENTS 1

static char grid_is_row_full(struct grid *grid, int row_index);
static void grid_mark_row_broken(struct grid *grid, int row_index);
static char grid_is_shape_overlapping(struct grid *grid);
static void grid_affix_shape(struct grid *grid);
static void grid_set_game_over(struct grid *grid);
static int grid_calculate_drop_delay(char current_level);

/* Initializes a new grid. Returns 1 for success, 0 on failure. */
char grid_init(struct grid *grid, char level, char empty) {

  int i;

  /* Set the entire grid to blanks. */
  for (i = 0; i < GRID_SIZE; ++i) {
    grid->blocks[i] = 0;
  }

  /* Verify that the level is appropriate. */
  if (level > MAX_LEVEL) {
    level = MAX_LEVEL;
  }
  if (level < MIN_LEVEL) {
    level = MIN_LEVEL;
  }

  grid->level = level;
  grid->lines_to_level = LINES_PER_LEVEL;
  grid->lines_cleared = 0;
  grid->score = 0;
  grid->shape_index = NO_ACTIVE_SHAPE;
  grid->shape_row = 0;
  grid->shape_col = 0;
  grid->shape_rotation = 0;
  grid->drop_delay = grid_calculate_drop_delay(grid->level);
  grid->drop_counter = 0;
  grid->contains_broken_lines = 0;
  grid->game_over = 0;
  grid->animation_index = 0;
  grid->animation_counter = 0;

  if (empty) {
    grid->next_shape_index = NO_ACTIVE_SHAPE;
  } else {
    grid->next_shape_index = rand() % SHAPES;
  }

  return 1;
}

/* Gets the value of the block at the given row and column. */
unsigned char grid_get_block_value(struct grid *grid, int row, int col) {
  unsigned char block_value;
  int shape_row, shape_col;

  block_value = grid->blocks[row * GRID_COLUMNS + col];

  /* Check to see if the current row/col is part of the active shape. Only
     check if the block is empty and there is still an active shape on the
     grid. */
  if (block_value == EMPTY_BLOCK && grid->shape_index != NO_ACTIVE_SHAPE) {
    shape_row = row - grid->shape_row;
    shape_col = col - grid->shape_col;

    if (shape_row >= 0 && shape_row < SHAPE_ROWS &&
	shape_col >= 0 && shape_col < SHAPE_COLUMNS) {
      block_value = shape_get_value(grid->shape_index,
				    grid->shape_rotation,
				    shape_row, shape_col);
    }
  }
  return block_value;
}
  

/* Updates the active shape on the grid and checks for cleared lines. */
void grid_update(struct grid *grid) {

  int i;
  int lines_recently_cleared;

  /* Don't do anything if the game is over. */
  if (grid->game_over) {
    return;
  }

  /* If there are broken lines on the grid, run through the animation sequence and then clear them away when finished. */
  if (grid->contains_broken_lines) {
    ++grid->animation_counter;
    if (grid->animation_counter >= TICKS_PER_FRAME) {
      ++grid->animation_index;
      grid->animation_counter = 0;
    }

    if (grid->animation_index >= BREAKING_BRICK_FRAMES) {
      grid->animation_index = 0;
      grid_sweep_broken_lines(grid);
    }
    return;
  }


  /* Check for any full rows. */
  lines_recently_cleared = 0;
  if (grid->shape_index == NO_ACTIVE_SHAPE && !grid->contains_broken_lines) {
    for (i = 0; i < GRID_ROWS; ++i) {
      if (grid_is_row_full(grid, i)) {
	grid_mark_row_broken(grid, i);
	++grid->lines_cleared;
	++lines_recently_cleared;
	grid->contains_broken_lines = 1;
      }
    }

    grid->score += (POINTS_PER_LINE * lines_recently_cleared * lines_recently_cleared);
    if (grid->level <= MAX_LEVEL &&
	grid->lines_cleared >= grid->lines_to_level) {
      
      ++grid->level;
      grid->drop_delay = grid_calculate_drop_delay(grid->level);
      grid->lines_to_level += LINES_PER_LEVEL;
    }
  
    /* If there is no active shape on the board, move the next shape to the current one, unless we are waiting for the broken lines to be cleared. */
    if (!grid->contains_broken_lines) {
      grid->shape_index = grid->next_shape_index;
      grid->next_shape_index = rand() % SHAPES;
      grid->shape_row = 0;
      grid->shape_col = 3;
      grid->shape_rotation = 0;
      grid->drop_counter = 0;

      /* If the new shape just added overlaps with an existing block on the grid, then the game is over. */
      if (grid_is_shape_overlapping(grid)) {
	grid_set_game_over(grid);
	return;
      }
    }
  }

  if (grid->shape_index != NO_ACTIVE_SHAPE) {
    ++grid->drop_counter;
    if (grid->drop_counter >= grid->drop_delay) {
      grid->drop_counter = 0;
      grid_move_shape_down(grid);
    }
  }
}

/* Checks if the given player's row at the index has no empty blocks. */
static char grid_is_row_full(struct grid *grid, int row_index) {
  int start_index, i, block_value;

  start_index = row_index * GRID_COLUMNS;

  /* If there are any empty blocks in the row, return 0 early. */
  for (i = 0; i < GRID_COLUMNS; ++i) {
    block_value = grid->blocks[start_index + i];
    if (block_value == EMPTY_BLOCK || block_value == BROKEN_BLOCK) {
      return 0;
    }
  }
  return 1;
}

/* Marks each block in the given player's row as broken. */
static void grid_mark_row_broken(struct grid *grid, int row_index) {

  int i, start_index;

  start_index = row_index * GRID_COLUMNS;

  for (i = 0; i < GRID_COLUMNS; ++i) {
    grid->blocks[start_index + i] = BROKEN_BLOCK;
  }
}

/* Clears any blocks marked as "cleared" from the grid. These are only kept around until the breaking blocks animation is allowed to complete. */
void grid_sweep_broken_lines(struct grid *grid) {
  int row, col;
  int clear_row, clear_row_index, new_value;
  int row_index;

  for (row = 0; row < GRID_ROWS ; ++row) {
    row_index = row * GRID_COLUMNS;

    /* Check the first block of each row, and if it is marked as cleared then we can go ahead and wipe it out. */
    if (grid->blocks[row_index] == BROKEN_BLOCK) {

      /* Clear out this row, and move down all blocks above it. If it's the top row, just mark them as EMPTY_BLOCK. */

      for (clear_row = row; clear_row >= 0; --clear_row) {

	clear_row_index = clear_row * GRID_COLUMNS;
	for (col = 0; col < GRID_COLUMNS; ++col) {

	  if (clear_row == 0) {
	    new_value = EMPTY_BLOCK;
	  } else {
	    new_value = grid->blocks[clear_row_index + col - GRID_COLUMNS];
	  }
	  grid->blocks[clear_row_index + col] = new_value;
	}
      }
    }
  }
  grid->contains_broken_lines = 0;
}

/* Moves the active shape one block to the left if possible. */
void grid_move_shape_left(struct grid *grid) {
  if (grid->shape_index == NO_ACTIVE_SHAPE) {
    return;
  }

  --grid->shape_col;
  if (grid_is_shape_overlapping(grid)) {
    ++grid->shape_col;
  }
}

/* Moves the active shape one block to the right if possible. */
void grid_move_shape_right(struct grid *grid) {
  if (grid->shape_index == NO_ACTIVE_SHAPE) {
    return;
  }

  ++grid->shape_col;
  if (grid_is_shape_overlapping(grid)) {
    --grid->shape_col;
  }
}

/* Moves the active shape one block down. If the shape hits another block or the bottom of the grid, it is affixed to the grid and returns 1. Otherwise, return 0. */
char grid_move_shape_down(struct grid *grid) {
  char overlapping;

  if (grid->shape_index == NO_ACTIVE_SHAPE) {
    return 0;
  }

  overlapping = 0;

  ++grid->shape_row;
  if (grid_is_shape_overlapping(grid)) {
    --grid->shape_row;
    grid_affix_shape(grid);
    overlapping = 1;
  }
  return overlapping;
}

/* Check if the current position of the active shape is overlapping any other blocks on the grid or if it is outside of the grid area. */
static char grid_is_shape_overlapping(struct grid *grid) {
  int row, col;
  int shape_value;
  int grid_row;
  int grid_col;

  for (row = 0; row < SHAPE_ROWS; ++row) {
    for (col = 0; col < SHAPE_COLUMNS; ++col) {
      shape_value = shape_get_value(grid->shape_index, grid->shape_rotation, row, col);

      if (shape_value > 0) {
	grid_row = row + grid->shape_row;
	grid_col = col + grid->shape_col;

	if (grid_row < 0 || grid_row >= GRID_ROWS ||
	    grid_col < 0 || grid_col >= GRID_COLUMNS) {
	  return 1;
	}

	if (grid->blocks[(grid_row * GRID_COLUMNS) + grid_col] > 0) {
	  return 1;
	}
      }
    }
  }
  return 0;
}

/* Copies the active shape onto the grid and invalidates the current shape so that it cannot be moved until a new shape is generated. */
static void grid_affix_shape(struct grid *grid) {
  int row, col;
  int shape_value;
  int grid_row;
  int grid_col;
  int index;

  for (row = 0; row < SHAPE_ROWS; ++row) {
    for (col = 0; col < SHAPE_COLUMNS; ++col) {
      shape_value = shape_get_value(grid->shape_index, grid->shape_rotation, row, col);
      if (shape_value > 0) {

	grid_row = row + grid->shape_row;
	grid_col = col + grid->shape_col;
	index = grid_row * GRID_COLUMNS + grid_col;
	grid->blocks[index] = shape_value;
      }
    }
  }
  grid->shape_index = NO_ACTIVE_SHAPE;
}

/* Continuously moves a shape down until it hits another block or the bottom of the grid. */
void grid_drop_shape(struct grid *grid) {
  if (grid->shape_index == NO_ACTIVE_SHAPE) {
    return;
  }

  while (!grid_move_shape_down(grid)) {}
}

/* Rotates the current shape. */
void grid_rotate_shape(struct grid *grid) {
  int original_rotation;

  if (grid->shape_index == NO_ACTIVE_SHAPE) {
    return;
  }

  /* The rotations are saved in the shapes table (shapes.c). Increment the index in the table to get a new rotation. */
  original_rotation = grid->shape_rotation++;
  if (grid->shape_rotation >= ROTATIONS) {
    grid->shape_rotation = 0;
  }

  /* If the rotation isn't in an invalid position, we can keep the changes, otherwise we have to try a few
     more possibilities. */
  if (!grid_is_shape_overlapping(grid)) {
    return;
  }

  /* Try moving the piece to the left or the right and see if that works. */
  grid->shape_col++;
  if (!grid_is_shape_overlapping(grid)) {
    return;
  }

  grid->shape_col -= 2;
  if (!grid_is_shape_overlapping(grid)) {
    return;
  }

  /* This piece has no space to rotate, so revert it back to the original position. */
  grid->shape_col++;
  grid->shape_rotation = original_rotation;
}

/* Marks the grid as game over and sets each of the blocks to the game over state. */
static void grid_set_game_over(struct grid *grid) {
  int i;

  grid->game_over = 1;
  grid_affix_shape(grid);

  
  for (i = 0; i < GRID_SIZE; ++i) {
    if (grid->blocks[i] != EMPTY_BLOCK) {
      grid->blocks[i] = BROKEN_BLOCK;
    }
  }
}

/* Determines how long it should take for the shape to drop. */
static int grid_calculate_drop_delay(char current_level) {
  return BASE_DROP_DELAY + (MAX_LEVEL - current_level) * DELAY_INCREMENTS;
}
