#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct animation_s {
    uint16_t** frames;
    uint16_t num_frames;
	uint16_t cur_frame;
    uint16_t speed;
	bool enabled;
	uint32_t start_time;
} animation_t;

animation_t* create_animation(uint16_t speed, uint16_t num_args, ...);
void start_animation(animation_t* anim);
uint16_t* animate(animation_t* anim);
uint16_t* stop_animation(animation_t* anim);
void destroy_animation(animation_t* anim);

#endif