#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ili9341.h"
#include "char_tiles.h"
#include "animation.h"
#include "ds4.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240
#define TILE_HEIGHT 16
#define TILE_WIDTH 16

static uint16_t pos_x = 0;
static uint16_t pos_y = 0;
static bool triggered = false;

void ds4_cb(sony_ds4_input_report_t* input_report, size_t report_size) {

  triggered = true;
  switch(input_report->dpad) {
    case 0:
      pos_y = (pos_y - 1) < 0 ? 0 : pos_y - 1;
      break;
    case 2:
      pos_x = (pos_x + 1) > SCREEN_WIDTH-16 ? SCREEN_WIDTH-16 : pos_x + 1;
      break;
    case 4:
      pos_y = (pos_y + 1) > SCREEN_HEIGHT-16 ? SCREEN_HEIGHT-16 : pos_y + 1;
      break;
    case 6:
      pos_x = (pos_x - 1) < 0 ? 0 : pos_x - 1;
      break;
  }
}

int main() {

    ds4_init(ds4_cb);
    scene_init();

    scene_set_background

    animation_t* run_normal = create_animation(10, 4, sprite_0, sprite_1, sprite_2, sprite_3);
    animation_t* run_fast = create_animation(50, 4, sprite_0, sprite_1, sprite_2, sprite_3);

    start_animation(run_normal);
    start_animation(run_fast);
    
    uint32_t fake_counter = 0;

    while (true) {
        ds4_task();

        if (fake_counter > 0 && fake_counter < 160000 && fake_counter % 500 == 0) {
            pos_y = (pos_y + 1) > SCREEN_HEIGHT-16 ? SCREEN_HEIGHT-16 : pos_y + 1;
            PRINT_TILE(pos_x, pos_y, animate(run_fast));
        } else if (fake_counter > 200000 && fake_counter < 360000 && fake_counter % 500 == 0) {
            pos_y = (pos_y - 1) < 0 ? 0 : pos_y - 1;
            PRINT_TILE(pos_x, pos_y, animate(run_fast));
        } else if (fake_counter > 400000) {
            fake_counter = 0;
        } else {
            PRINT_TILE(pos_x, pos_y, animate(run_normal));
        }
        
        fake_counter++;
        // PRINT_TILE(16, 48, animate(run_fast));
    }

    stop_animation(run_normal);
    stop_animation(run_fast);
}