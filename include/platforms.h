#ifndef __PLATFORMS_H__
#define __PLATFORMS_H__

#include "entity.h"

/**
 * @brief Create a new player entity
 * @param position where to spawn the aguman at
 * @param type of platform to be created(0-4)
 * @return NULL on error, or an player entity pointer on success
 */
Entity *platforms_new(Vector3D position, int type);


#endif
