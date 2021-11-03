#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "Entity.h"


/**
 * @brief detects when entities touch each other
 * @param 
 */
void collision_detection_test(Entity* self, Entity* other);
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