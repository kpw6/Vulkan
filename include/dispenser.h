#ifndef __DISPENSER_H__
#define __DISPENSER_H__

#include "entity.h"
#include "physics.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @param player is the type of player you choose from (0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity* dispenser_new(Vector3D position);

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @param player is the type of player you choose from (0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity* arrow_new(Vector3D position);

/**
 * @brief spikes touch function
 * @param spikes
 * @param player
 */
void dispenser_onTouch(Entity* self, Entity* other);

#endif