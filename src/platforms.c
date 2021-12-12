#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "platforms.h"

int x = 0;
void platforms_think(Entity *self);
void platforms_update(Entity *self);
void mplatforms_ontouch(Entity* self, Entity* other);

Entity *platforms_new(Vector3D position, int type)
{
    SJson* json, * pjson;
    json = sj_load("config/entities.json");
    if (!json) {
        slog("failed to load json file for the giant data");
        return;
    }
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("failed player entity");
        return NULL;
    }
    
    switch (type) {
    case 0: //moving platform
        pjson = sj_object_get_value(json, "movingplatform");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }
        ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
        ent->think = platforms_think;
        ent->update = platforms_update;
        ent->touch = mplatforms_ontouch;
        break;
    case 1: //ladder
        ent->model = gf3d_model_load("mplatform");
        ent->think = platforms_think;
        ent->update = platforms_update;
        ent->touch = mplatforms_ontouch;
        break;
    case 2: //moneky bars
        ent->model = gf3d_model_load("mplatform");
        ent->think = platforms_think;
        ent->update = platforms_update;
        ent->touch = mplatforms_ontouch;
        break;
    case 3: //trapdoor
        ent->model = gf3d_model_load("mplatform");
        ent->think = platforms_think;
        ent->update = platforms_update;
        ent->touch = mplatforms_ontouch;
        break;
    case 4:
        ent->model = gf3d_model_load("mplatform");
        ent->think = platforms_think;
        ent->update = platforms_update;
        ent->touch = mplatforms_ontouch;
        break;
    }
    ent->radius = 0.1;
    ent->position = position;
    return ent;
}


//Code for the moving platform touch function
void mplatforms_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += 0.8;
    other->gravity = 0;
}
void ladder_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += 0.8;
    other->gravity = 0;
}
void monkeybars_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += 0.8;
    other->gravity = 0;
}
void trapdoor_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += 0.8;
    other->gravity = 0;
}
/*
void mplatforms_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += 0.8;
    other->gravity = 0;
}
*/
void platforms_think(Entity *self)
{
    switch (x) {
    case 0: 
        if (self->position.x > .9) {
            x = 1;
            break;
        }
        self->position.x += .01; 
        break;
    case 1:
        if (self->position.x < -.9) {
            x = 0;
            break;
        }
        self->position.x -= .01;
        break;
    }
    //self->min = vector3d_add(self->position, self->position, vector3d(-1,-1,-1));
    //self->max = vector3d_add(self->position, self->position, vector3d(1, 1, 1));
}

void platforms_update(Entity *self)
{
   // physics_update(self);
}

/*eol@eof*/
