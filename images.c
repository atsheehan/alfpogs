#include "images.h"
#include "SDL_image.h"
#include <stdio.h>
#include <stdlib.h>

static int image_dimensions[DIMENSIONS_PER_IMAGE * NUMBER_OF_IMAGES] = {
  /* width, height, x, y */
  640, 480, 0, 0,
  640, 480, 0, 1000, /* TODO */
  20, 20, 0, 480,
  20, 20, 20, 480,
  20, 20, 40, 480,
  20, 20, 60, 480,
  20, 20, 80, 480,
  20, 20, 100, 480,
  20, 20, 120, 480,
  20, 20, 0, 500,
  640, 480, 0, 520
};

SDL_Surface **images_load(const char *filename) {

  SDL_Rect source_rect;
  int i;
  SDL_Surface *master_image;
  SDL_Surface **images_array;
  int index;

  master_image = IMG_Load(filename);
  if (master_image == NULL) {
    fprintf(stderr, "IMG_Load: %s\n", IMG_GetError());
    return NULL;
  }

  images_array = malloc(sizeof(SDL_Surface *) * NUMBER_OF_IMAGES);
  if (images_array == NULL) {
    fprintf(stderr, "unable to allocate memory for the images_array\n");
    return NULL;
  }

  for (i = 0; i < NUMBER_OF_IMAGES; i++) {
    index = i * DIMENSIONS_PER_IMAGE;

    source_rect.w = image_dimensions[index];
    source_rect.h = image_dimensions[index + 1];
    source_rect.x = image_dimensions[index + 2];
    source_rect.y = image_dimensions[index + 3];

    images_array[i] = SDL_CreateRGBSurface(SDL_SWSURFACE, source_rect.w, source_rect.h, COLOR_DEPTH, 0, 0, 0, 0);

    if (images_array[i] == NULL) {
      fprintf(stderr, "SDL_CreateRGBSurface: %s\n", SDL_GetError());
      images_free(images_array, i);
      return NULL;
    }

    SDL_SetColorKey(images_array[i], SDL_SRCCOLORKEY, SDL_MapRGB(images_array[i]->format, 255, 0, 255));

    if (SDL_BlitSurface(master_image, &source_rect, images_array[i], NULL) == -1) {
      fprintf(stderr, "SDL_BlitSurface: %s\n", SDL_GetError());
      images_free(images_array, i + 1);
      return NULL;
    }
  }

  return images_array;
}

void images_free(SDL_Surface **images, int number_of_images) {
  int i;
  for (i = 0; i < number_of_images; i++) {
    SDL_FreeSurface(images[i]);
  }
  free(images);
}
