#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "entity.h"
#include "world.h"

/**
 * @brief detects when entities touch each other
 * @param 
 */
Bool collision_detection_test(Entity* self, Entity* other);

Bool circle_collision_test(Entity* self, Entity* other);
/**
 * @brief checks to see if an entity has a hitbox
 * @param entity that is being checked
 */
Bool checkminmax(Entity* self);

/**
 * @brief applies gravity to an entity
 * @param entity that gravity is applied too
 */
void applyGravity(Entity* self);

/**
 * @brief updates physics affects
 * @param entity that physics is applied too
 */
void physics_update(Entity* self);

#endif