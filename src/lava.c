#include "SDL_Timer.h"
#include "simple_logger.h"

#include "lava.h"
#include "entity.h"

static Bool active;
void lava_onTouch(Entity* self, Entity* other);

Entity* lava_new(Vector3D position)
{
    Entity* ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("lava");
    ent->scale = vector3d(1, 1, 1);
    ent->position = position;
    ent->touch = lava_onTouch;
    gfc_matrix_scale(ent->modelMat, ent->scale);
    active = true;
    ent->radius = 1;
    return ent;
}

void lava_onTouch(Entity* self, Entity* other) {
    other->health -= 1;
}
