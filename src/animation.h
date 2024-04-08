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

/*
* Creates a new animation object with the provides sprites as bitmaps
* @param    speed       speed of switching through sprites in frmaes per second
* @param    num_args    number of sprites
* @param    ...         sprites as bitmaps
* @return   animation_t animation object       
*/
animation_t* create_animation(uint16_t speed, uint16_t num_args, ...);

/*
* Starts the internal animation timer for the particular animation object
* @param    anim        animation object for which the timer is to be started
*/
void start_animation(animation_t* anim);

/*
* Returns the appropriate frame for the time instant. Hence this method will need to be 
* called inside a forever loop so that it keeps displaying the next frame
* @param    anim        animation object
*/
uint16_t* animate(animation_t* anim);

/*
* Stops the internal animation timer for the particular animation object
* @param    anim        animation object
* @return   uint16_t    the last frame to be displayed
*/
uint16_t* stop_animation(animation_t* anim);

/*
* Free all allocated memory for the animation object
* @param    anim        animation object
*/
void destroy_animation(animation_t* anim);

#endif