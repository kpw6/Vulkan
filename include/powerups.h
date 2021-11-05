#ifndef __POWERUPS_H__
#define __POWERUPS_H__

#include "entity.h"

/**
* @brief creates a new powerup
* @param position is where the entity spawns
* @param is the type of powerup that is created (0-4)
*/
Entity powerups_new(Vector3D position, int type);

/**
* @brief update for powerups
* @param the powerup that is updated
*/
void powerups_think(Entity* self);

/**
* @brief update for powerups
* @param self is powerup that is touched
* @param self Entity that is affected
*/
void powerups_ontouch(Entity* self, Entity* other);



#endif