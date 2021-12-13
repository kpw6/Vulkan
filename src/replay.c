#include "simple_logger.h"
#include "gfc_types.h"

#include "replay.h"

Vector3D position;

Entity* replay_new(Vector3D positions) {
	Entity* ent = NULL;
	ent = entity_new();
	position = positions;
	ent->model = gf3d_model_load("dino");
    ent->position = vector3d(0, 0, -19);
	ent->think = replay_think;
	ent->scale = vector3d(0.1, 0.1, 0.1);


}

void replay_think(Entity* self) {
    if (self->position.x - position.x >= 0) {
        self->position.x -= .01;
    }
    else {
        self->position.x += .01;
    }
    if (self->position.y - position.y >= 0) {
        self->position.y -= .01;
    }
    else {
        self->position.y += .01;
    }
    if (vector2d_equal(self->position, position)) {
        vector3d(0, 0, -19);
    }

}