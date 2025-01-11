#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ili9341.h"
#include "engine/animation.h"
#include "ds4.h"
#include "scene.h"
#include "level_tiles.h"
#include "scene.h"

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

    scene_set_background_fill_tile(full_brick, 15, 20);
    
    uint32_t fake_counter = 0;
    // animation_t* run_normal = create_animation(10, 4, sprite_0, sprite_1, sprite_2, sprite_3);
    // animation_t* run_fast = create_animation(50, 4, sprite_0, sprite_1, sprite_2, sprite_3);

    // start_animation(run_normal);
    // start_animation(run_fast);

    entity_t player = {
        0, 
        0, 
        sprite_0,
    };

    while (true) {
        ds4_task();

        if (fake_counter > 0 && fake_counter < 320000 && fake_counter % 1000 == 0) {
            pos_y = (pos_y + 1) > SCREEN_HEIGHT-16 ? SCREEN_HEIGHT-16 : pos_y + 1;
            scene_move_entity(&player, pos_x, pos_y);
        } else if (fake_counter > 400000 && fake_counter < 720000 && fake_counter % 500 == 0) {
            pos_y = (pos_y - 1) < 0 ? 0 : pos_y - 1;
            scene_move_entity(&player, pos_x, pos_y);
        } else if (fake_counter > 800000) {
            fake_counter = 0;
        } 
        
        fake_counter++;
    }

    // stop_animation(run_normal);
    // stop_animation(run_fast);
}
