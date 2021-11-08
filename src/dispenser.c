#include "simple_logger.h"
#include "dispenser.h"

void dispenser_think(Entity* self);

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
    gfc_matrix_scale(ent->modelMat, ent->scale);
    return ent;
}

void dispenser_think(Entity* self) {
    Entity* arrow;
    arrow = arrow_new(self);
    entity_free(arrow);
}