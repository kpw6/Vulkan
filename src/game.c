#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"

#include "entity.h"
#include "agumon.h"
#include "player.h"
#include "world.h"
#include "platforms.h"
#include "powerups.h"
#include "spikes.h"
#include "dispenser.h"
#include "lava.h"
#include "deathball.h"

int main(int argc,char *argv[])
{
    int done = 0;
    int a;
    Uint8 validate = 0;
    const Uint8 * keys;
    Entity* player;
    Entity* spikes;
    Entity* powerup;
    
    World *w;
    
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
    
    w = world_load("config/testworld.json");

    // main game loop
	slog_sync();
    gf3d_camera_set_scale(vector3d(1,1,1));
    
    slog("gf3d main loop begin");
    player = player_new(vector3d(0,0,0), 0);
    platforms_new(vector3d(0, 20, -15));
    spikes = spikes_new(vector3d(0, 10, -19.5));
    powerup = powerups_new(vector3d(0, 15, -19), 4);
    dispenser_new(vector3d(3, 10, -19));
    lava_new(vector3d(5, 5, -19.5));
    deathball_new(vector3d(5, 20, -19.5));
    for (int i = 0; i <= 4; i++) {
       powerups_new(vector3d(i + 5, i + 10, -19), i);
    }

    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
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
         
        gf3d_vgraphics_render_end();


        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
    }    
    
    world_delete(w);
    
    vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());    
    //cleanup
    slog("gf3d program end");
    slog_sync();
    return 0;
}

/*eol@eof*/
