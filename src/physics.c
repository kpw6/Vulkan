#include "physics.h"
#include "simple_logger.h"

//https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects
Bool collision_detection_test(Entity* self, Entity* other) {
	if (!self) return;
	if (!other) return;
	float d1x = self->min.x - other->max.x;
	float d2x = other->min.x - self->max.x;
	float d1y = self->min.y - self->max.y;
	float d2y = other->min.y - self->max.y;
	float d1z = self->min.z - other->max.z;
	float d2z = other->min.z - self ->max.z;

	if (d1x > 0.0f && d1y > 0.0f || d1z > 0.0f) return false;
	else if (d2x > 0.0f && d2y > 0.0f  || d2z > 0.0f) return false;

	return true;

}
Bool circle_collision_test(Entity* self, Entity* other) {
	float d1x = self->position.x - other->position.x;
	float d1y = self->position.y - other->position.y;
	float d1z = self->position.z - other->position.z;
	return (sqrt(pow(d1x, 2) + pow(d1y, 2) + pow(d1z, 2)));
}

Bool checkminmax(Entity* self) {
	if (!self) return;
	if (self->min.x > 0 || self->min.z > 0 || self->min.y > 0 || self->max.x > 0 || self->max.z > 0 || self->max.y > 0) {
		return true;
	}
	return false;
}

void applyGravity(Entity* self) {
	if (!self)return;
	if (self->position.z > -18.7) {
		self->position.z -= 0.3;
	}
}
