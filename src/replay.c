#include "simple_logger.h"
#include "gfc_types.h"

#include "replay.h"

Entity* replay_new(Vector3D position) {
	Entity* ent = NULL;
	ent = entity_new();
	ent->position = position;
	ent->model = gf3d_model_load("dino");
	ent->think = replay_think;
	ent->scale = vector3d(0.1, 0.1, 0.1);

}

void replay_think(Entity* self) {

}