#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"


void player_think(Entity *self);
void player_update(Entity *self);

Entity *player_new(Vector3D position)
{
    Entity *ent = NULL;
    
    ent = entity_new();
    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }
    ent->model = gf3d_model_load("dino");
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->rotation.x = M_PI;
    gf3d_camera_set_rotation(ent->rotation);
    //applyGravity(ent);
    return ent;
}


void player_think(Entity *self)
{
    if (!self)return;
    Vector3D forward;
    Vector3D right;
    Vector3D up;
    const Uint8 * keys;
    keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame

    vector3d_angle_vectors(self->rotation, &forward, &right, &up);
    vector3d_set_magnitude(&forward,0.1);
    vector3d_set_magnitude(&right,0.1);
    vector3d_set_magnitude(&up,0.1);

    if (keys[SDL_SCANCODE_W])
    {   
        vector3d_add(self->position,self->position,forward);
        vector3d_add(self->min, self->min, forward);
        vector3d_add(self->max, self->max, forward);
    }
    if (keys[SDL_SCANCODE_S])
    {
        vector3d_add(self->position,self->position,-forward);   
        vector3d_add(self->min, self->min, -forward);
        vector3d_add(self->max, self->max, -forward);
    }
    if (keys[SDL_SCANCODE_D])
    {
        vector3d_add(self->position,self->position,right);
        vector3d_add(self->min, self->min, right);
        vector3d_add(self->max, self->max, right);
    }
    if (keys[SDL_SCANCODE_A])    
    {
        vector3d_add(self->position,self->position,-right);
        vector3d_add(self->min, self->min, -right);
        vector3d_add(self->max, self->max, -right);
    }
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.010;
    if (keys[SDL_SCANCODE_Z])self->position.z -= 0.010;   
    if (keys[SDL_SCANCODE_UP])self->rotation.x -= 0.030;
    if (keys[SDL_SCANCODE_DOWN])self->rotation.x += 0.030;
    if (keys[SDL_SCANCODE_LEFT])self->rotation.z -= 0.030;
    if (keys[SDL_SCANCODE_RIGHT])self->rotation.z += 0.030;

}

void player_update(Entity *self)
{
    if (!self)return;
    gf3d_camera_set_position(self->position, vector3d(0, 10, 0));
    //gf3d_camera_set_rotation(self->rotation);
    //physics_update(self);
}

/*eol@eof*/
