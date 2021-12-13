#include "physics.h"
#include "simple_logger.h"

//https://www.toptal.com/game/video-game-physics-part-ii-collision-detection-for-solid-objects
int rect_detection_test(Entity* self, Entity* other) {
	if (!self) return;
	if (!other) return;
	float d1x = self->min.x - other->max.x;
	float d2x = other->min.x - self->max.x;
	float d1y = self->min.y - self->max.y;
	float d2y = other->min.y - self->max.y;
	float d1z = self->min.z - other->max.z;
	float d2z = other->min.z - self ->max.z;

	if (d1x > 0.0f && d1y > 0.0f && d1z > 0.0f) return 0;
	else if (d2x > 0.0f && d2y > 0.0f  && d2z > 0.0f) return 0;

	return ;

}
float circle_collision_test(Entity* self, Entity* other) {
	float d1x = self->position.x - other->position.x;
	float d1y = self->position.y - other->position.y;
	float d1z = self->position.z - other->position.z;
	return (sqrt(pow(d1x, 2) + pow(d1y, 2) + pow(d1z, 2)));
}

int rect_circle_detection_test(Entity* self, Entity* other) {
	float one = max(self->min.x, min(other->position.x, self->max.x)) - other->position.x;
	float two = max(self->min.y, min(other->position.y, self->max.y)) - other->position.y;
	float three = max(self->min.z, min(other->position.z, self->max.z)) - other->position.z;

	return (sqrt(pow(one, 2) + pow(two, 2) + pow(three, 2)));
	
}

int checkminmax(Entity* self) {
	if (!self) return;
	if (self->min.x != 0 && self->max.x != 0) {
		return 0;
	}
	return 1;
}

int collision_detection_test(Entity* self, Entity* other) {
	if (!self) return;
	if (!other) return;
	if (self->radius != 0 && other->radius != 0) {
		if (circle_collision_test(self, other) <= self->radius + other->radius) {
			return 0;
		}
	}
	else if (self->radius != 0 && !checkminmax(other)) {
		if (rect_circle_detection_test(other, self) < self->radius) {
			return 0;
			}
		}
	else if (other->radius != 0 && !checkminmax(self)) {
		if (rect_circle_detection_test(self, other) < other->radius) {
			return 0;
		}
	}
	else {
		if (checkminmax(self) && checkminmax(other)) {
			return 1;
		}
		if (!rect_detection_test(self, other)) {
			return 0;
		}
	}

	return 1;
}

void applyGravity(Entity* self) {
	if (!self)return;
	if (self->position.z > -18.7) {
		self->position.z -= 0.3;
	}
	if (self->position.z < -25) {
		self->health -= 1;
	}
}
