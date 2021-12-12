#ifndef __REPLAY_H__
#define __REPLAY_H__

#include "entity.h"

Entity* replay_new(Vector3D position);

void replay_think(Entity* self);

#endif