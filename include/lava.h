#ifndef __LAVA_H__
#define __LAVA_H__

#include "entity.h"
#include "physics.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @param player is the type of player you choose from (0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity* lava_new(Vector3D position);

/**
 * @brief spikes touch function
 * @param lava
 * @param player
 */
void lava_ontouch(Entity* self, Entity* other);

#endif