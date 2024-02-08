#include <stdarg.h>
#include <stdlib.h>
#include "animation.h"
#include "pico/stdlib.h"

animation_t* create_animation(uint16_t speed, uint16_t num_args, ...) {
	va_list args;
    va_start(args, num_args);
	
	animation_t* new_animation = (animation_t*) malloc(sizeof(animation_t));
	new_animation->frames = (uint16_t**) malloc(sizeof(uint16_t*) * num_args);

	for (int i = 0; i < num_args; i++) {
		new_animation->frames[i] = va_arg(args, uint16_t*);
	}

	va_end(args);

	new_animation->num_frames = num_args;
	new_animation->speed = speed;
	new_animation->cur_frame = 0;
	new_animation->enabled = false;
	new_animation->start_time = 0UL;

	return new_animation;
}

void start_animation(animation_t* anim) {
	anim->enabled = true;
	anim->start_time = time_us_32();
}

uint16_t* animate(animation_t* anim) {
	uint32_t now = time_us_32();
	if (((now - anim->start_time) > (1000000/anim->speed)) && anim->enabled) {
		anim->start_time = now;
		anim->cur_frame = (anim->cur_frame + 1) % anim->num_frames;
	}
	return anim->frames[anim->cur_frame];
}

uint16_t* stop_animation(animation_t* anim) {
	anim->enabled = false;
	anim->start_time = 0;
	anim->cur_frame = 0;

	return anim->frames[anim->cur_frame];
}

void destroy_animation(animation_t* anim) {
	free(anim->frames);
	free(anim);
}


