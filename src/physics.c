#include "physics.h"
#include "simple_logger.h"

typedef struct {
	Vector3D p1;
	Vector3D p2;
	Vector3D p3;
}triangle3D;

//https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects
Bool collision_detection_test(Entity* self, World* other) {
    float d1x = self->min.x - other->max.x;
    float d1y = other->min.y - self->max.y;
    float d2x = self->min.x - other->max.x;
    float d2y = other->min.y - self->max.y;
    float d1z = self->min.z - other->max.z;
    float d2z = other->min.z - self->max.z;

    if (d1x > 0.0 || d1y > 0.0 /* || d2z > 0.0*/)
        return false;

    if (d2x > 0.0 || d2y > 0.0 /* || d2z > 0.0 */ )
        return false;

    return true;
}

void applyGravity(Entity* self) {
	if (!self)return;
	self->gravity = 0.5;
}

void physics_update(Entity* self) {
	if (!self)return;
    if(self->min.z > -19)
	    self->position.z -= self->gravity;
}