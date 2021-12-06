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
    entity_assign_sound(ent, "sounds/oof.mp3");
    ent->model = gf3d_model_load("dino");
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->rotation.x = M_PI;
    gf3d_camera_set_rotation(ent->rotation);
    applyGravity(ent);
    ent->scale = vector3d(0.1, 0.1, 0.1);
    gfc_matrix_scale(ent->modelMat, ent->scale);
    //ent->velocity = vector3d(1, 1, 1);
    ent->health = 1;
    ent->jPower = 3;
    ent->jPack = false;
    ent->radius = 0.05;
    ent->speed = 0.1;
    return ent;
}

Bool isJumping(Entity* self) {
    if (self->position.z > -17) {
        return true;
    }
    return false;
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

    if (keys[SDL_SCANCODE_UP] && self->position.y < 48)
    {   
        self->position.y += self->speed;
    }
    if (keys[SDL_SCANCODE_DOWN] && self->position.y > -48)
    {
        self->position.y -= self->speed;
    }
    if (keys[SDL_SCANCODE_LEFT] && self->position.x > -55)
    {
        self->position.x -= self->speed;
    }
    if (keys[SDL_SCANCODE_RIGHT] && self->position.x < 45)    
    {
        self->position.x += self->speed;
    }

    switch (self->jPack) {
    case true:
        if (keys[SDL_SCANCODE_SPACE])self->position.z += 0.5;
        break;
    case false:
        if (!isJumping(self)) {
            if (keys[SDL_SCANCODE_SPACE])self->position.z += self->jPower;
        }
        break;
    }

}

void player_update(Entity *self)
{
    if (!self)return;
    gf3d_camera_set_position(self->position, vector3d(0, 5, 0));
    //gf3d_camera_set_rotation(self->rotation);
    applyGravity(self);
    if (self->health <= 0) entity_onDeath(self);
}

/*eol@eof*/
