#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "platforms.h"

int x = 0;
void platforms_think(Entity *self);
void platforms_update(Entity *self);

Entity *platforms_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("failed player entity");
        return NULL;
    }
    
    ent->model = gf3d_model_load("mplatform");
    ent->think = platforms_think;
    ent->update = platforms_update;
    ent->position = position;
    return ent;
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
    //self->min = vector3d_add(self->position, self->position, vector3d(-1,-1,-1));
    //self->max = vector3d_add(self->position, self->position, vector3d(1, 1, 1));
}

void platforms_update(Entity *self)
{
   // physics_update(self);
}

/*eol@eof*/
