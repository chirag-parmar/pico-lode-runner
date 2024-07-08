#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>

typedef struct {
    uint16_t pos_x;
    uint16_t pos_y;
    uint16_t* tile;
} entity_t;

void set_static_background_tiles(uint16_t** background_tiles, uint16_t num_rows, uint16_t num_cols);
void move_entity(entity_t* entity, uint16_t x, uint16_t y);
void scene_init();

#endif // SCENE_H