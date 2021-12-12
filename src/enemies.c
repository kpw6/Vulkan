#include "gfc_types.h"
#include "simple_json.h"
#include "simple_logger.h"

#include "enemies.h"

int y = 0;

Entity* big_monster_new(Vector3D position) {
	SJson *json, *ejson;
	json = sj_load("config/entities.json");
	if (!json) {
		slog("failed to load json file for the giant data");
		return;
	}
	ejson = sj_object_get_value(json, "giant");
	if (!ejson) {
		slog("failed to find world object in entity config");
		sj_free(json);
		return NULL;
	}
	Entity* ent = entity_new();
	if (!ent) return;

	ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(ejson, "model")));
	ent->position = position;
	ent->radius = 0.5;
	ent->think = big_monster_think;
	ent->scale = vector3d(9, 9, 9);
	ent->touch = big_monster_ontouch;
	sj_free(json);
}

void big_monster_think(Entity* self) {
	self->position.y += 0.02;
}

void big_monster_ontouch(Entity* self, Entity* other) {
	other->health -= 1;

}
Entity* cross_walk_new(Vector3D position) {
	SJson *json, *ejson;
	json = sj_load("config/entities.json");
	if (!json) {
		slog("failed to load json file for the jwalker data");
		return;
	}
	ejson = sj_object_get_value(json, "jwalker");
	if (!ejson) {
		slog("failed to find world object in entity config");
		sj_free(json);
		return NULL;
	}
	Entity* ent = entity_new();
	if (!ent) return;

	ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(ejson, "model")));
	ent->position = position;
	ent->radius = .1;
	ent->think = cross_walk_think;
	ent->scale = vector3d(0.1, 0.1, 0.1);
	ent->touch = cross_walk_ontouch;
	ent->rotation = vector3d(20, 80, -90);
	sj_free(json);
}
void cross_walk_think(Entity* self) {
	switch (y) {
	case 0:
		if (self->position.x > 20.9) {
			y = 1;
			break;
		}
		self->position.x += .01;
		break;
	case 1:
		if (self->position.x < 19.1) {
			for (float i = 0; i < 20; i += 0.0001f);
			y = 0;
			break;
		}
		self->position.x -= .01;
		break;
	}


}

void cross_walk_ontouch(Entity* self, Entity* other) {
	other->health -= 1;

}