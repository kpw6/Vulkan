#include <SDL.h>            

#include "simple_logger.h"
#include "simple_json.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_sprite.h"
#include "gfc_audio.h"

#include "entity.h"
#include "timer.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "platforms.h"
#include "powerups.h"
#include "spikes.h"
#include "dispenser.h"
#include "lava.h"
#include "deathball.h"
#include "enemies.h"

int main(int argc,char *argv[])
{
    int done = 0, menu = 0;
    int a;
    int type;
    Uint8 validate = 0;
    const Uint8 * keys;
    Entity* player;
    Entity* spikes;
    Entity* powerup;
    
    Sprite* mouse = NULL;
    Sprite* menuitem1 = NULL;
    Sprite* menuitem2 = NULL;
    Sprite* menuitem3 = NULL;
    Sprite* menuitem4 = NULL;
    Sprite* menuitem5 = NULL;
    int mousex, mousey;
    float mouseFrame = 0;
    float item1frame = 0, item2frame = 0, item3frame = 0, item4frame = 0, item5frame = 0;
    Timer* timer = NULL;
    World *w;

    SDL_TimerID time;
    SDL_TimerCallback callback;
    
    for (a = 1; a < argc;a++)
    {
        if (strcmp(argv[a],"-disable_validate") == 0)
        {
            validate = 0;
        }
    }
    
    init_logger("gf3d.log");    
    slog("gf3d begin");
    gf3d_vgraphics_init(
        "gf3d",                 //program name
        1200,                   //screen width
        700,                    //screen height
        vector4d(0.51,0.75,1,1),//background color
        0,                      //fullscreen
        validate                //validation
    );
	slog_sync();
    
    entity_system_init(1024);
    gfc_audio_init(1024, 1, 1, 5, true, true);
    gfc_sound_init(1024);
    SDL_Init(32);

    slog_sync();
    gf3d_camera_set_scale(vector3d(1, 1, 1));
    slog("gf3d menu loop begin");
    mouse = gf3d_sprite_load("images/pointer.png", 32, 32, 16);
    menuitem1 = gf3d_sprite_load("images/type1.png", 360, 360, 2);
    menuitem2 = gf3d_sprite_load("images/type2.png", 360, 360, 2);
    menuitem3 = gf3d_sprite_load("images/type3.png", 360, 360, 2);
    menuitem4 = gf3d_sprite_load("images/type4.png", 360, 360, 2);
    menuitem5 = gf3d_sprite_load("images/type5.png", 360, 360, 2);

    while (!menu) {
        SDL_PumpEvents();
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        SDL_GetMouseState(&mousex, &mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;

        if (mousex >= 10 && mousex <= 190 && mousey >= 250  && mousey <= 425) {
            item1frame = 1;
            if ((SDL_GetMouseState(&mousex, &mousey) & SDL_BUTTON_LMASK) != 0)  {
                type = 0;
                menu = 1;
            }
        }
        else if (mousex >= 257 && mousex <= 437 && mousey >= 250 && mousey <= 425) {
            item2frame = 1;
            if ((SDL_GetMouseState(&mousex, &mousey) & SDL_BUTTON_LMASK) != 0) {
                type = 1;
                menu = 1;
            }
        }
        else if (mousex >= 504 && mousex <= 684 && mousey >= 250 && mousey <= 425) {
            item3frame = 1;
            if ((SDL_GetMouseState(&mousex, &mousey) & SDL_BUTTON_LMASK) != 0) {
                type = 2;
                menu = 1;
            }
        }
        else if (mousex >= 751 && mousex <= 931 && mousey >= 250 && mousey <= 425) {
            item4frame = 1;
            if ((SDL_GetMouseState(&mousex, &mousey) & SDL_BUTTON_LMASK) != 0) {
                type = 3;
                menu = 1;
            }
        }
        else if (mousex >= 1000 && mousex <= 1180 && mousey >= 250 && mousey <= 425) {
            item5frame = 1;
            if ((SDL_GetMouseState(&mousex, &mousey) & SDL_BUTTON_LMASK) != 0) {
                type = 4;
                menu = 1;
            }
        }
        else {
            item1frame = 0;
            item2frame = 0;
            item3frame = 0;
            item4frame = 0;
            item5frame = 0;
        }

        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());
        gf3d_vgraphics_render_start();
            gf3d_sprite_draw(mouse, vector2d(mousex, mousey), vector2d(1, 1), (Uint32)mouseFrame);
            gf3d_sprite_draw(menuitem1, vector2d(10, 250), vector2d(1, 1), (Uint32)item1frame);
            gf3d_sprite_draw(menuitem2, vector2d(257, 250), vector2d(1, 1), (Uint32)item2frame);
            gf3d_sprite_draw(menuitem3, vector2d(504, 250), vector2d(1, 1), (Uint32)item3frame);
            gf3d_sprite_draw(menuitem4, vector2d(751, 250), vector2d(1, 1), (Uint32)item4frame);
            gf3d_sprite_draw(menuitem5, vector2d(1000, 250), vector2d(1, 1), (Uint32)item5frame);
        gf3d_vgraphics_render_end();
    }
    gf3d_sprite_free(menuitem1);
    gf3d_sprite_free(menuitem2);
    gf3d_sprite_free(menuitem3);
    gf3d_sprite_free(menuitem4);
    gf3d_sprite_free(menuitem5);

    w = world_load("config/testworld.json");

    // main game loop
	slog_sync();
    timer_assign(timer);
    gf3d_camera_set_scale(vector3d(1,1,1));
    slog("gf3d main loop begin");
    player = player_new(vector3d(0, 0, -15), type, "config/entities.json");
    platforms_new(vector3d(0, -20, -19), 0);
    spikes = spikes_new(vector3d(0, 10, -19.5));
    dispenser_new(vector3d(3, 10, -19));
    lava_new(vector3d(5, 5, -19.5));
    deathball_new(vector3d(5, 20, -19.5));
    for (int i = 0; i <= 4; i++) {
       powerups_new(vector3d(i + 5, i + 10, -19), i);
    }
    platforms_new(vector3d(-20, 20, -19), 1);
    platforms_new(vector3d(20, 20, -17), 2);
    platforms_new(vector3d(30, 40, -19), 3);
    platforms_new(vector3d(28, 20, -19), 4);
    big_monster_new(vector3d(0, -50, -10));
    cross_walk_new(vector3d(20, -20, -19));
    snail_new(vector3d(-50, -50, -19));
    multiplyer_new(vector3d(-10, -10, -19));
    archer_new(vector3d(-30, -10, -19));
    while(!done)
    {
  
        SDL_PumpEvents();   // update SDL's internal event structures
        //timer_update(timer);
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        SDL_GetMouseState(&mousex, &mousey);

        mouseFrame += 0.01;
        if (mouseFrame >= 16)mouseFrame = 0;
        entity_think_all();
        entity_update_all();
        entity_physics_all();
        gf3d_camera_update_view();
        gf3d_camera_get_view_mat4(gf3d_vgraphics_get_view_matrix());

        // configure render command for graphics command pool
        // for each mesh, get a command and configure it from the pool
        gf3d_vgraphics_render_start();

                world_draw(w);
                entity_draw_all();

                gf3d_sprite_draw(mouse, vector2d(mousex, mousey), vector2d(1, 1), (Uint32)mouseFrame);
         
        gf3d_vgraphics_render_end();


        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    world_delete(w);
    gfc_sound_clear_all();
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
