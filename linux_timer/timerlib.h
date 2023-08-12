#ifndef _LTIMER_H
#define _LTIMER_H

#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*******************************************
* ltimer states
*******************************************/
typedef enum
{
	TIMER_INIT,
	TIMER_RUNNING,
	TIMER_DELETED,
	TIMER_CANCELLED,
	TIMER_PAUSED,
	TIMER_RESUMED

} TIMER_STATE_T;

/*******************************************
* ltimer_t structure
*******************************************/
typedef struct _ltimer
{
	timer_t posix_timer;
	void *user_arg;

	/* in milisec */
	unsigned long exp_timer;

	/*in milisec */
	unsigned long sec_exp_timer;

	/* how many times timer can perform */
	uint32_t threshold;

	/* Callback function to perform
	   after timer count to 0 */
	void (*cb)(struct _ltimer*, void *);

	/* is it expotetial_backoff timer */
	bool expotential_backoff;

	/*
	 * 	dynamic attributes of timer
         */

	/* how many time till end */
	unsigned long time_remaining;

	/* how many times timer called cb func */
	uint32_t invokation_ctr;

	struct itimerspec ts;
	unsigned long exp_back_off_time;
	TIMER_STATE_T timer_state;

} ltimer_t;

/*******************************************
* ltimer_t constructor
* return: pointer to wrap_timer_t in succes
          NULL in failure
*******************************************/
ltimer_t *
ltimer_setup(
	    void (*)(ltimer_t *, void *),
	    unsigned long,
            unsigned long,
            uint32_t,
            void *,
            bool);

/*******************************************
* ltimer_t destructor
* return: 0 - success
	  -1 - failure
*******************************************/
int ltimer_delete(ltimer_t **timer);

/*******************************************
* Start counting
*******************************************/
void ltimer_start(ltimer_t *timer);

/*******************************************
* Pause timer counting
*******************************************/
void
ltimer_pause(ltimer_t *timer);

/*******************************************
* Timer resume counting
*******************************************/
void
ltimer_resume(ltimer_t *timer);

/*******************************************
* Timer restart counting from the
* beggining
*******************************************/
void ltimer_restart(ltimer_t *timer);

/*******************************************
* Change timer time settings
*******************************************/
void
ltimer_reschedule(ltimer_t *timer,
		  unsigned long exp_time,
		  unsigned long sec_exp_time);

/*******************************************
* Stop timer counting and restart it
*******************************************/
void ltimer_cancel(ltimer_t *timer);

/*******************************************
* Get remaining timer time
* return: time in milisec
*******************************************/
unsigned long
ltimer_get_rem_time(ltimer_t *);

/*******************************************
* Get current timer state
* return: timer state
*******************************************/
static inline TIMER_STATE_T
ltimer_get_state(ltimer_t *timer)
{
        return timer->timer_state;
}

#endif /* !define _LTIMER_H */
