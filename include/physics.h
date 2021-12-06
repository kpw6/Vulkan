#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "entity.h"
#include "world.h"

/**
 * @brief detects when entities touch through rectangle colliders
 * @param 
 */
int rect_detection_test(Entity* self, Entity* other);

/**
 * @brief detects when entities touch through circle colliders
 * @param
 */
Bool circle_collision_test(Entity* self, Entity* other);

/**
 * @brief detects when entities touch through rect and circle colliders
 * @param
 */
Bool rect_circle_detection_test(Entity* self, Entity* other);

/**
 * @brief checks to see if an entity has a hitbox
 * @param entity that is being checked
 */
Bool checkminmax(Entity* self);

/**
 * @brief runs the correct collision test and does it.
 * @param self is self entity
 * @param other is touched entity
 */
int collision_detection_test(Entity* self, Entity* other);

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