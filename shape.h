#ifndef SHAPE_H
#define SHAPE_H

#define SHAPES 7
#define ROTATIONS 4
#define SHAPE_ROWS 4
#define SHAPE_COLUMNS 4
#define SHAPE_SIZE SHAPE_ROWS * SHAPE_COLUMNS

unsigned char shape_get_value(int shape, int rotation, int row, int col);
void shape_fill_grid(int shape, unsigned char *grid);
unsigned char *shape_get_grid(int index);

#endif /* SHAPE_H */
