#ifndef __SPIKES_H__
#define __SPIKES_H__

#include "entity.h"
#include "physics.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @param player is the type of player you choose from (0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity* spikes_new(Vector3D position);

/**
 * @brief spikes touch function
 * @param spikes
 * @param player
 */
void spikes_onTouch(Entity* self, Entity* other);

#endif
