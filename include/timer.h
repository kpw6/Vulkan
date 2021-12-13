#ifndef __TIMER_H__
#define __TIMER_H__

typedef struct Timer_S{
	float currentTime;
	float prevTime;
	float deltaTime;
	float frameCount;
}Timer;

/*
* @brief makes all variables start with 0
* @param the timer to assign var to
*/
Timer* timer_assign(Timer* time);
/*
* @brief updates the current timer
* @param the timer to update
*/
void timer_update(Timer* timer);

/*
* @brief Gets the delta time for usage
* @returns deltatime
*/
float get_DeltaTime();

#endif