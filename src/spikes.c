#include "SDL_Timer.h"
#include "simple_logger.h"

#include "spikes.h"
#include "entity.h"

static Bool active;
void spikes_onTouch(Entity* self, Entity* other);

Entity* spikes_new(Vector3D position)
{
    Entity* ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("spikes");
    ent->scale = vector3d(0.1, 0.1, 0.1);
    ent->position = position;
    ent->touch = spikes_onTouch;
    gfc_matrix_scale(ent->modelMat, ent->scale);
    active = true;
    ent->radius = 0.05;
    return ent;
}

void spikes_onTouch(Entity* self, Entity* other) {
    other->health -= 1;
    slog("healthy");
}
