#include "shape.h"

static unsigned char shapes[SHAPES * ROTATIONS * SHAPE_ROWS * SHAPE_COLUMNS] = {
  /* Block shape */
  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0, 

  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,

  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,

  0, 1, 1, 0,
  0, 1, 1, 0,
  0, 0, 0, 0,
  0, 0, 0, 0,

  /* T shape */
  0, 0, 2, 0,
  0, 2, 2, 0,
  0, 0, 2, 0,
  0, 0, 0, 0,

  0, 0, 2, 0,
  0, 2, 2, 2,
  0, 0, 0, 0,
  0, 0, 0, 0,

  0, 0, 2, 0,
  0, 0, 2, 2,
  0, 0, 2, 0,
  0, 0, 0, 0,

  0, 0, 0, 0, 
  0, 2, 2, 2,
  0, 0, 2, 0,
  0, 0, 0, 0,

  /* L shape */
  0, 3, 0, 0, 
  0, 3, 0, 0,
  0, 3, 3, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 3, 3, 3,
  0, 3, 0, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 3, 3, 0,
  0, 0, 3, 0,
  0, 0, 3, 0,

  0, 0, 0, 0,
  0, 0, 3, 0,
  3, 3, 3, 0,
  0, 0, 0, 0,

  /* Reverse-L shape */
  0, 0, 4, 0, 
  0, 0, 4, 0,
  0, 4, 4, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 4, 0, 0,
  0, 4, 4, 4,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 4, 4, 0,
  0, 4, 0, 0,
  0, 4, 0, 0,

  0, 0, 0, 0,
  4, 4, 4, 0,
  0, 0, 4, 0,
  0, 0, 0, 0,

  /* I shape */
  0, 0, 5, 0, 
  0, 0, 5, 0,
  0, 0, 5, 0,
  0, 0, 5, 0,

  0, 0, 0, 0,
  0, 0, 0, 0,
  5, 5, 5, 5,
  0, 0, 0, 0,

  0, 5, 0, 0,
  0, 5, 0, 0,
  0, 5, 0, 0,
  0, 5, 0, 0,

  0, 0, 0, 0,
  5, 5, 5, 5,
  0, 0, 0, 0,
  0, 0, 0, 0,

  /* Squiggly shape */
  0, 0, 6, 0, 
  0, 6, 6, 0,
  0, 6, 0, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 6, 6, 0,
  0, 0, 6, 6,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 0, 6, 0,
  0, 6, 6, 0,
  0, 6, 0, 0,

  0, 0, 0, 0,
  6, 6, 0, 0,
  0, 6, 6, 0,
  0, 0, 0, 0,

  /* Reverse-squiggly shape */
  0, 7, 0, 0, 
  0, 7, 7, 0,
  0, 0, 7, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 0, 7, 7,
  0, 7, 7, 0,
  0, 0, 0, 0,

  0, 0, 0, 0,
  0, 7, 0, 0,
  0, 7, 7, 0,
  0, 0, 7, 0,

  0, 0, 0, 0,
  0, 7, 7, 0,
  7, 7, 0, 0,
  0, 0, 0, 0,
};


/* Returns the value of the shape at the given coordinates. */
unsigned char shape_get_value(int shape, int rotation, int row, int col) {
  int shape_index = shape * SHAPE_ROWS * SHAPE_COLUMNS * ROTATIONS;
  int rotation_index = rotation * SHAPE_COLUMNS * SHAPE_ROWS;
  int row_index = row * SHAPE_COLUMNS;
  int block_index = shape_index + rotation_index + row_index + col;

  return shapes[block_index];
}

/* Copies the given shape and its rotation onto the supplied grid. */
void shape_fill_grid(int shape, unsigned char *grid) {
  int shape_index = (shape * ROTATIONS * SHAPE_SIZE);

  int i;
  for (i = 0; i < SHAPE_SIZE; ++i) {
    grid[i] = shapes[shape_index + i];
  }
}

unsigned char *shape_get_grid(int index) {
  int array_index = (index * ROTATIONS * SHAPE_SIZE);
  return (shapes + array_index);
}
