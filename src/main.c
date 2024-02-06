#include "pico/stdlib.h"
#include "ili9341.h"
#include "char_tiles.h"

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

    PRINT_TILE(0, 0, sprite_0);
    PRINT_TILE(0, 16, sprite_1);
    PRINT_TILE(0, 32, sprite_2);
    PRINT_TILE(0, 48, sprite_3);
    PRINT_TILE(0, 64, sprite_4);
    PRINT_TILE(0, 80, sprite_5);
    PRINT_TILE(0, 96, sprite_6);
    PRINT_TILE(0, 112, sprite_7);
    PRINT_TILE(0, 128, sprite_8);
    PRINT_TILE(0, 144, sprite_9);
    PRINT_TILE(0, 160, sprite_10);
    PRINT_TILE(0, 176, sprite_11);
    PRINT_TILE(0, 192, sprite_12);
    PRINT_TILE(0, 208, sprite_13);
    PRINT_TILE(0, 224, sprite_14);
    PRINT_TILE(0, 240, sprite_15);
    PRINT_TILE(0, 256, sprite_16);
    PRINT_TILE(0, 272, sprite_17);
    PRINT_TILE(0, 288, sprite_18);
    PRINT_TILE(0, 304, sprite_19);
    
    PRINT_TILE(16, 0, sprite_20);
    PRINT_TILE(16, 16, sprite_21);
    PRINT_TILE(16, 32, sprite_22);
    PRINT_TILE(16, 48, sprite_23);
    PRINT_TILE(16, 64, sprite_24);
    PRINT_TILE(16, 80, sprite_25);
    PRINT_TILE(16, 96, sprite_26);
    PRINT_TILE(16, 112, sprite_27);
    PRINT_TILE(16, 128, sprite_28);
    PRINT_TILE(16, 144, sprite_29);
    PRINT_TILE(16, 160, sprite_30);
    PRINT_TILE(16, 176, sprite_31);
    PRINT_TILE(16, 192, sprite_32);
    PRINT_TILE(16, 208, sprite_33);
    PRINT_TILE(16, 224, sprite_34);
    PRINT_TILE(16, 240, sprite_35);
    PRINT_TILE(16, 256, sprite_36);
    PRINT_TILE(16, 272, sprite_37);
    PRINT_TILE(16, 288, sprite_38);
    PRINT_TILE(16, 304, sprite_39);

    PRINT_TILE(32, 0, sprite_40);
    PRINT_TILE(32, 16, sprite_41);
    PRINT_TILE(32, 32, sprite_42);
    PRINT_TILE(32, 48, sprite_43);
    PRINT_TILE(32, 64, sprite_44);
    PRINT_TILE(32, 80, sprite_45);
    PRINT_TILE(32, 96, sprite_46);
    PRINT_TILE(32, 112, sprite_47);
    PRINT_TILE(32, 128, sprite_48);
    PRINT_TILE(32, 144, sprite_49);
    PRINT_TILE(32, 160, sprite_50);
    PRINT_TILE(32, 176, sprite_51);
    PRINT_TILE(32, 192, sprite_52);
    PRINT_TILE(32, 208, sprite_53);
    PRINT_TILE(32, 224, sprite_54);
    PRINT_TILE(32, 240, sprite_55);
    PRINT_TILE(32, 256, sprite_56);
    PRINT_TILE(32, 272, sprite_57);
    PRINT_TILE(32, 288, sprite_58);
    PRINT_TILE(32, 304, sprite_59);

    while (true)
    {
        
        sleep_ms(500);
    }
}