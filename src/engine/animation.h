#ifndef _ANIMATIONS_H_
#define _ANIMATIONS_H_

#include <stdint.h>

typedef struct animation_s {
    uint16_t** frames;
    uint16_t num_frames;
    uint16_t cur_frame;
} animation_t;

/*
* Creates a new animation object with the provided sprites as frames
* @param    anim        animation object of type animation_t
* @param    num_frames  number of sprites/frames
* @param    frames      array of frames
*/
#define create_animation(anim, num_frames, frames) do {\
  anim.frames = frames; \
  anim.num_frames = num_frames; \
  anim.cur_frame = 0; \
}

/*
* Returns the appropriate frame for the time instant. Hence this method will need to be 
* called inside a forever loop so that it keeps displaying the next frame
* @param    anim        animation object of type animation_t*
*/
#define get_next_frame(anim) (anim->frames[(++(anim->cur_frame) % anim->num_frames)];)

/*
* Stops the internal animation timer for the particular animation object
* @param    anim        animation object of type animation_t*
*/
#define stop_animation(anim) (anim->cur_frame = 0;)

#endif
