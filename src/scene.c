#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hardware/spi.h"
#include "ili9341.h"
#include "char_tiles.h"
#include "animation.h"
#include "scene.h"
#include "game.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TILE_HEIGHT 16
#define TILE_WIDTH 16

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define PRINT_TILE(x, y, tile) LCD_WriteBitmap(x, y, TILE_HEIGHT, TILE_WIDTH, tile);

static uint16_t* frame;
static uint16_t dirty_rect[3*TILE_HEIGHT*TILE_WIDTH];

void scene_set_background_tiles(uint16_t** background_tiles, uint16_t num_rows, uint16_t num_cols) {
    for (uint16_t row = 0; row < num_rows; row++) {
        for (uint16_t col = 0; col < num_cols; col++) {
            PRINT_TILE(col * TILE_WIDTH, row * TILE_HEIGHT, background_tiles[row * num_cols + col]);
            for (uint16_t i = 0; i < TILE_HEIGHT; i++) {
                memcpy(&frame[(row * TILE_HEIGHT + i) * SCREEN_WIDTH + col * TILE_WIDTH], &background_tiles[row * num_cols + col][i * TILE_WIDTH], TILE_WIDTH * sizeof(uint16_t));
            }
        }
    }
}

void scene_set_background_fill_tile(uint16_t* background_tile, uint16_t num_rows, uint16_t num_cols) {
    for (uint16_t row = 0; row < num_rows; row++) {
        for (uint16_t col = 0; col < num_cols; col++) {
            PRINT_TILE(col * TILE_WIDTH, row * TILE_HEIGHT, background_tile);
            for (uint16_t i = 0; i < TILE_HEIGHT; i++) {
                memcpy(&frame[(row * TILE_HEIGHT + i) * SCREEN_WIDTH + col * TILE_WIDTH], &background_tile[i * TILE_WIDTH], TILE_WIDTH * sizeof(uint16_t));
            }
        }
    }
}

void scene_move_tile(uint16_t* tile, coordinates_t* old_pos, coordinates_t* new_pos) {
    if (new_pos->x == old_pos->x && new_pos->y == old_pos->y) {
        return;
    }
    
    uint16_t w_dash = abs(old_pos->x - new_pos->x) + TILE_WIDTH;
    uint16_t h_dash = abs(old_pos->y - new_pos->y) + TILE_HEIGHT;
    uint16_t x_dash = min(old_pos->x, new_pos->x);
    uint16_t y_dash = min(old_pos->y, new_pos->y);

    for (uint16_t row = 0; row < h_dash; row++) {
        memcpy(&dirty_rect[row * TILE_WIDTH], &frame[(y_dash + row) * SCREEN_WIDTH + x_dash], w_dash * sizeof(uint16_t));
    }

    LCD_WriteBitmap(x_dash, y_dash, w_dash, h_dash, dirty_rect);
    PRINT_TILE(new_pos->x, new_pos->y, tile);
}

void scene_init() {
    // TODO: parameterize these values but abstract it out to a config file
    LCD_setPins(13, 9, 14, 10, 11);
    LCD_setSPIperiph(spi1);
    LCD_initDisplay();
    LCD_setRotation(3);

    frame = (uint16_t*)malloc(SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(uint16_t));
}
