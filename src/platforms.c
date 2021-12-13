#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "platforms.h"

int x = 0;
void platforms_think(Entity *self);
void platforms_update(Entity *self);
void mplatforms_ontouch(Entity* self, Entity* other);
void ladder_ontouch(Entity* self, Entity* other);
void monkeybars_ontouch(Entity* self, Entity* other);
void trapdoor_ontouch(Entity* self, Entity* other);
void rope_ontouch(Entity* self, Entity* other);


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
        ent->radius = 1;
        break;
    case 1: //ladder
        ent->model = gf3d_model_load("mplatform");
        ent->touch = ladder_ontouch;
        ent->scale = vector3d(0.5, 0.5, 20);
        ent->radius = 1;
        break;
    case 2: //moneky bars
        ent->model = gf3d_model_load("mplatform");
        ent->touch = monkeybars_ontouch;
        ent->scale = vector3d(0.5, 5, 1);
        ent->radius = 5;
        break;
    case 3: //trapdoor
        ent->model = gf3d_model_load("mplatform");
        ent->touch = trapdoor_ontouch;
        ent->radius = 1;
        break;
    case 4: //rope
        ent->model = gf3d_model_load("mplatform");
        ent->touch = rope_ontouch;
        ent->scale = vector3d(0.1, 0.1, 20);
        ent->radius = 1;
        break;
    }
    //ent->radius = 2;
    ent->position = position;
    return ent;
}


//Code for the moving platform touch function
void mplatforms_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    slog("you are toching platform");
    other->position.z += 0.8;
}
void ladder_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z += .5;
    other->gravity = 0;
}
void monkeybars_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z = -18;
}
void trapdoor_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.z -= 10;
    other->gravity = 0;
    self->scale = (vector3d(0.1, 1, 20));
}

void rope_ontouch(Entity* self, Entity* other) {
    if (!self) return;
    if (!other) return;
    other->position.y += 10;
}

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
}

void platforms_update(Entity *self)
{
   // physics_update(self);
}

/*eol@eof*/
