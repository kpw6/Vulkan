#include "SDL_Timer.h"
#include "simple_logger.h"

#include "spikes.h"
#include "entity.h"

int p = 0;
void deathball_think(Entity* self);
void deathball_ontouch(Entity* self, Entity* other);

Entity* deathball_new(Vector3D position)
{
    Entity* ent = NULL;

    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("cube");
    ent->scale = vector3d(0.1, 0.1, 0.1);
    ent->position = position;
    ent->touch = deathball_ontouch;
    ent->think = deathball_think;
    gfc_matrix_scale(ent->modelMat, ent->scale);
    ent->radius = 0.05;
    return ent;
}


void deathball_think(Entity* self) {
    {
        switch (p) {
        case 0:
            if (self->position.x > .9) {
                p = 1;
                break;
            }
            self->position.x += .01;
            break;
        case 1:
            if (self->position.x < -.9) {
                p = 0;
                break;
            }
            self->position.x -= .01;
            break;
        }
    }
}
void deathball_ontouch(Entity* self, Entity* other) {
    other->health -= 1;
    slog("deathball touch");
}
