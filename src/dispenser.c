#include "simple_logger.h"
#include "dispenser.h"

void dispenser_think(Entity* self);
void arrow_ontouch(Entity* self, Entity* other);
Entity* arro = NULL;

Entity* dispenser_new(Vector3D position) {
    Entity* ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("cube");
    ent->scale = vector3d(0.1, 0.1, 0.1);
    ent->think = dispenser_think;
    ent->position = position;
    ent->radius = .2;
    gfc_matrix_scale(ent->modelMat, ent->scale);
    return ent;
}

Entity* arrow_new(Entity* dispenser) {
    Entity* ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("spikes");
    ent->scale = vector3d(0.1, 0.1, 0.1);
    ent->position = dispenser->position;
    ent->radius = 0.2;
    gfc_matrix_scale(ent->modelMat, ent->scale);
    ent->touch = arrow_ontouch;
    return ent;
}

void dispenser_think(Entity* self) {    
    if (!arro) {
    arro = arrow_new(self);
    }
    arro->position.x -= 0.1;
    if (arro->position.x < -40) {
        arro->position = self->position;
    }
    
}

void arrow_ontouch(Entity* self, Entity* other) {
    other->health -= 1;
}