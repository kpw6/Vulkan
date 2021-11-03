#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "entity.h"
#include "physics.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the player at
 * @return NULL on error, or an player entity pointer on success
 */
Entity *player_new(Vector3D position);


#endif
