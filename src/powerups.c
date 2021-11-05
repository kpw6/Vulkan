#include "powerups.h"
#include "simple_logger.h"

static int ptype;

void powerups_think(Entity *self);
void powerups_ontouch(Entity* self, Entity* other);

Entity powerups_new(Vector3D position, int type) {
	ptype = type;
	Entity* ent = entity_new();
	if (!ent) {
		slog("failure to make a powerup");
		return;
	}
	switch (type) {
	case 0: //double speed
		ent->model = gf3d_model_load("upgrade_ds");
		break;
	case 1: //super jump
		ent->model = gf3d_model_load("upgrade_sj");
		break;
	case 2: //jetpack
		ent->model = gf3d_model_load("upgrade_jp");
		break;
	case 3: //double jump
		ent->model = gf3d_model_load("upgrade_dj");
		break;
	case 4: //second heart
		ent->model = gf3d_model_load("upgrade_sh");
		break;
	}
	ent->think = powerups_think;
	ent->touch = powerups_ontouch;
	ent->position = position;
	ent->scale = vector3d(0.2, 0.2, 0.2);
	gfc_matrix_scale(ent->modelMat, ent->scale);

}

void powerups_think(Entity* self) {

}

void powerups_ontouch(Entity* self, Entity* other) {
	switch (ptype) {
	case 0: //double speed
		vector3d_multiply(other->velocity, vector3d(2, 2, 2));
		break;
	case 1: //super jump
		break;
	case 2: //jetpack
		break;
	case 3: //double jump
		break;
	case 4: //second heart
		break;
	}
}