#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "physics.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @param player is the type of player you choose from (0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity *player_new(Vector3D position, int player);


#endif
