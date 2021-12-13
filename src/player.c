#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_types.h"

#include "gf3d_camera.h"
#include "player.h"
#include "replay.h"
#include "timer.h"


void player_think(Entity *self);
void player_update(Entity *self);
void player_onDeath(Entity* self);
int echecker = 0;

Entity* player_new(Vector3D position, int player, char* filename)
{
    float *speed;
    Entity *ent = NULL;
    
    ent = entity_new();

    if (!ent)
    {
        slog("UGH OHHHH, no player for you!");
        return NULL;
    }

    SJson *json, *pjson;

    json = sj_load(filename);
    if (!json) {
        slog("failed to load json file (%s) for the player data", filename);
        return;
    }
    switch(player) {
    case 0: //all-around character
        pjson = sj_object_get_value(json, "player");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }

        ent->model = gf3d_model_load(sj_get_string_value((char *)sj_object_get_value(pjson, "model")));
        if (!ent->model) {
            slog("failed to load player model");
            sj_free(json);
            return;
        }
        ent->speed = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "speed")));
        ent->health = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "health")));;
        ent->jPower = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "jump")));;
        break;
    case 1: //bulky character
        pjson = sj_object_get_value(json, "heavyplayer");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }

        ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
        ent->speed = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "speed")));
        ent->health = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "health")));;
        ent->jPower = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "jump")));;
        break;
    case 2: //speedy character
        pjson = sj_object_get_value(json, "speedyplayer");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }

        ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
        ent->speed = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "speed")));
        ent->health = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "health")));;
        ent->jPower = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "jump")));;
        break;
    case 3: //jetpack master
        pjson = sj_object_get_value(json, "scientistplayer");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }

        ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
        ent->speed = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "speed")));
        ent->health = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "health")));;
        ent->jPower = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "jump")));;
        break;
    case 4: //other
        pjson = sj_object_get_value(json, "fifthplayer");
        if (!pjson) {
            slog("failed to find world object in entity config");
            sj_free(json);
            return NULL;
        }

        ent->model = gf3d_model_load(sj_get_string_value((char*)sj_object_get_value(pjson, "model")));
        ent->speed = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "speed")));
        ent->health = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "health")));;
        ent->jPower = atof(sj_get_string_value((char*)sj_object_get_value(pjson, "jump")));;
        break;

    }
    entity_assign_sound(ent, "sounds/oof.mp3");
    ent->think = player_think;
    ent->update = player_update;
    vector3d_copy(ent->position,position);
    ent->rotation.x = M_PI;
    gf3d_camera_set_rotation(ent->rotation);
    applyGravity(ent);
    ent->scale = vector3d(0.1, 0.1, 0.1);
    gfc_matrix_scale(ent->modelMat, ent->scale);
    ent->velocity = vector3d(1, 1, 1);
    ent->jPack = false;
    ent->radius = 1;
    ent->onDeath = player_onDeath;
    return ent;
}

Bool isJumping(Entity* self) {
    if (self->position.z > -17) {
        return true;
    }
    return false;
}

void player_onDeath(Entity* self) {
    if (!self)return;
    gfc_sound_play(self->sound, 0, 1, -1, -1);
    slog("wassup");
    if (echecker == 1) {
        entity_free(entity_latest());
        slog("this ran");
        echecker = 0;
    }
    replay_new(self->position);
    self->position = vector3d(0, 0, -15);
    self->health = 1;
    echecker = 1;

    //save data to leaderboard
    SJson *json, *sjson, *ljson;
    json = sj_load("config/leaderboard.json");
    if (!json) {
        slog("Failed to load file leaderboard");
        return;
    }
    ljson = sj_new_str("yeet");
    sj_save(ljson, "config/leaderboard.json");
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

    if (keys[SDL_SCANCODE_X]) {
        gf3d_camera_set_rotation(vector3d(-90, 0, 0));
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
