#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>
#include "animation.h"

void scene_set_background_tiles(uint16_t** background_tiles, uint16_t num_rows, uint16_t num_cols);
void scene_set_background_fill_tile(uint16_t* background_tile, uint16_t num_rows, uint16_t num_cols);
void scene_move_tile(uint16_t* tile, coordinates_t* old_pos, coordinates_t* new_pos);
void scene_init();

#endif // SCENE_H
