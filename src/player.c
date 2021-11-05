#include "simple_logger.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"


void player_think(Entity *self);
void player_update(Entity *self);

Entity* player_new(Vector3D position, int player)
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
    applyGravity(ent);
    ent->scale = vector3d(0.1, 0.1, 0.1);
    gfc_matrix_scale(ent->modelMat, ent->scale);
    ent->velocity = vector3d(1, 1, 1);
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

    if (keys[SDL_SCANCODE_UP])
    {   
        vector3d_add(self->position,self->position,-right);
    }
    if (keys[SDL_SCANCODE_DOWN])
    {
        vector3d_add(self->position,self->position,right);   
    }
    if (keys[SDL_SCANCODE_LEFT])
    {
        vector3d_add(self->position,self->position,-forward);
    }
    if (keys[SDL_SCANCODE_RIGHT])    
    {
        vector3d_add(self->position,self->position,forward);
    }
    if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.010;  

}

void player_update(Entity *self)
{
    if (!self)return;
    gf3d_camera_set_position(self->position, vector3d(0, 5, 0));
    //gf3d_camera_set_rotation(self->rotation);
    physics_update(self);
}

/*eol@eof*/
