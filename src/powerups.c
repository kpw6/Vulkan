#include "powerups.h"
#include "simple_logger.h"
#include "simple_json.h"
#include "physics.h"
#include "gfc_audio.h"

static int ptype;

void powerups_think(Entity *self);
void powerups_ontouch(Entity* self, Entity* other);

Entity* powerups_new(Vector3D position, int type) {
	SJson* json, * pjson;
	json = sj_load("config/entities.json");
	if (!json) {
		slog("failed to load json file for the giant data");
		return;
	}
	Entity* ent = entity_new();
	if (!ent) {
		slog("failure to make a powerup");
		return;
	}
	switch (type) {
	case 0: //double speed
		pjson = sj_object_get_value(json, "upgrade_ds");
		if (!pjson) {
			slog("failed to find world object in entity config");
			sj_free(json);
			return NULL;
		}
		ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
		break;
	case 1: //super jump
		pjson = sj_object_get_value(json, "upgrade_sj");
		if (!pjson) {
			slog("failed to find world object in entity config");
			sj_free(json);
			return NULL;
		}
		ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
		break;
	case 2: //jetpack
		pjson = sj_object_get_value(json, "upgrade_jp");
		if (!pjson) {
			slog("failed to find world object in entity config");
			sj_free(json);
			return NULL;
		}
		ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
		break;
	case 3: //double jump
		pjson = sj_object_get_value(json, "upgrade_dj");
		if (!pjson) {
			slog("failed to find world object in entity config");
			sj_free(json);
			return NULL;
		}
		ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
		break;
	case 4: //second heart
		pjson = sj_object_get_value(json, "upgrade_sh");
		if (!pjson) {
			slog("failed to find world object in entity config");
			sj_free(json);
			return NULL;
		}
		ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
		break;
	}
	entity_assign_sound(ent, "sounds/thunder.mp3");
	ent->think = powerups_think;
	ent->touch = powerups_ontouch;
	ent->position = position;
	ent->scale = vector3d(0.2, 0.2, 0.2);
	ent->rotation = vector3d(0, 0, 0);
	ent->radius = 0.1;
	gfc_matrix_scale(ent->modelMat, ent->scale);
	ent->type = type;
	

	return ent;
}

void powerups_think(Entity* self) {
	self->rotation.z += .01;

}

void powerups_ontouch(Entity* self, Entity* other) {
	switch (self->type) {
	case 0: //double speed
		other->speed *= 2;
		slog("powerup 1 active");
		break;
	case 1: //super jump
		slog("powerup 2 active");
		other->jPower *= 2;
		break;
	case 2: //jetpack
		slog("powerup 3 active");
		other->jPack = true;
		break;
	case 3: //double jump
		slog("powerup 4 active");
		other->doubleJump = true;
		break;
	case 4: //second heart
		other->health += 1;
		slog("powerup 5 active");
		break;
	}
	gfc_sound_play(self->sound, 0, 1, 0, -1);
	entity_free(self);
	slog("powerup dismantled");
}