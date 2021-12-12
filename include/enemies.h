#ifndef __ENEMIES_H__
#define __ENEMIES_H__

#include "entity.h"

/**
 * @brief Create a new Big Monster entity
 * @param position where to spawn the Big Monster at
 * @return NULL on error, or an player entity pointer on success
 */
Entity* big_monster_new(Vector3D position);

/**
 * @brief Think function for big monster entity
 * @param Entity that is using the function
 */
void big_monster_think(Entity* self);

/**
 * @brief Think function for big monster entity
 * @param Entity that touches the other entity
 */
void big_monster_ontouch(Entity* self, Entity* other);

/**
 * @brief Create a new Cross Walk entity
 * @param position where to spawn the Cross Walk at
 * @return NULL on error, or an player entity pointer on success
 */
Entity* cross_walk_new(Vector3D position);

/**
 * @brief Think function for big monster entity
 * @param Entity that is using the function
 */
void cross_walk_think(Entity* self);

/**
 * @brief Think function for big monster entity
 * @param Entity that touches the other entity
 */
void cross_walk_ontouch(Entity* self, Entity* other);

#endif