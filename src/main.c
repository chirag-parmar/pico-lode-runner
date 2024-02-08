#include "pico/stdlib.h"
#include "ili9341.h"
#include "char_tiles.h"
#include "animation.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TILE_HEIGHT 16
#define TILE_WIDTH 16

#define PRINT_TILE(x, y, tile) LCD_WriteBitmap(y, x, TILE_HEIGHT, TILE_WIDTH, tile);

int main()
{
    LCD_setPins(13, 9, 14, 10, 11);
    LCD_setSPIperiph(spi1);
    LCD_initDisplay();
    LCD_setRotation(1);

    animation_t* run_normal = create_animation(10, 4, sprite_0, sprite_1, sprite_2, sprite_3);
    animation_t* run_fast = create_animation(20, 4, sprite_0, sprite_1, sprite_2, sprite_3);

    start_animation(run_normal);
    start_animation(run_fast);
    
    while (true) {
        PRINT_TILE(16, 16, animate(run_normal));
        PRINT_TILE(16, 48, animate(run_fast));
    }

    stop_animation(run_normal);
    stop_animation(run_fast);
}