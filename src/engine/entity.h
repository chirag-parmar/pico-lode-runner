#ifndef GAME_H
#define GAME_H

#include <stdint.h>
#include "animation.h"

typedef struct {
    uint16_t x;
    uint16_t y;
} coordinates_t;

typedef struct {
    uint16_t x;
    uint16_t y;
} vector_t;

typedef uint8_t action_t;
typedef action_t (*force_handler_t)(vector_t* resultant_force);
typedef void (*action_handler_t)(void* entity, action_t action, uint16_t* output_frame);

// typedef void (*collision_handler_t)(entity_t* colliding_entity, uint8_t collision_percentage);
// typedef void (*trigger_handler_t)(void* trigger_data);
// typedef void (*immersion_feedback_t)(void* immersion_feedback_data);

typedef struct {
    uint8_t id;
    coordinates_t* pos;
    animation_t** animations;
    force_handler_t force_handler;
    action_handler_t action_handler;
} entity_t;

#define apply_force(output_force, existing_force, input_force) (\
  output_force->x = existing_force->x + input_force->x; \
  output_force->y = existing_force->y + input_force->y; \
)

#endif // GAME_H
