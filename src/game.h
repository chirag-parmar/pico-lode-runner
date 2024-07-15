#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "animation.h"

typedef struct {
    uint16_t x;
    uint16_t y;
} coordinates_t;

typedef void (*collision_handler_t)(entity_t* colliding_entity, uint8_t collision_percentage);
typedef void (*trigger_handler_t)(void* trigger_data);
typedef void (*immersion_feedback_t)(void* immersion_feedback_data);

typedef struct {
    coordinates_t pos;
    animation_t** animations;
    uint16_t num_animations;
    uint16_t current_animation;
    bool animate;
    collision_handler_t on_collision;
    trigger_handler_t on_trigger;
    immersion_feedback_t immersion_feedback;
} entity_t;

#endif // GAME_H