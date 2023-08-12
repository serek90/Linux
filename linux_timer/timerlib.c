#include "timerlib.h"
#include <assert.h>

static inline void
ltimer_set_state(ltimer_t *timer, TIMER_STATE_T timer_state)
{
        timer->timer_state = timer_state;
}

unsigned long
timespec_to_millisec(struct timespec *time)
{
	unsigned long msec =  time->tv_sec * 1000;
	msec += time->tv_nsec / 1000000;
	return msec;
}

void
ltimer_fill_itimerspec(struct timespec *ts,
                      unsigned long msec)
{
	ts->tv_sec = msec / 1000;
	ts->tv_nsec = (msec % 1000) * 1000000;
}

/*******************************************
* Special wrapper
********************************************/
void ltimer_cb_wrapper(union sigval args)
{
	ltimer_t *timer = (ltimer_t *)(args.sival_ptr);
	(timer->cb)(timer, timer->user_arg);

	if(ltimer_get_state(timer) == TIMER_RESUMED
	   && timer->sec_exp_timer)
	{
		ltimer_set_state(timer, TIMER_RUNNING);
	}
}

/*******************************************
* Start counting from passed time
*******************************************/
void ltimer_resurrect(ltimer_t *timer)
{
	/* Call UNIX API */
	int rc = timer_settime(timer->posix_timer,
                               0, &timer->ts, NULL);
	assert(rc >= 0);
}

/******************************************
* Start ltimer
******************************************/
void ltimer_start(ltimer_t *timer)
{
	if(timer)
	{
		assert(ltimer_get_state(timer) != TIMER_PAUSED);
		ltimer_resurrect(timer);
		ltimer_set_state(timer, TIMER_RUNNING);
	}
}

/*******************************************
* ltimer_t constructor
* return: pointer to wrap_timer_t in succes
          NULL in failure
*******************************************/
ltimer_t * ltimer_setup(
            void (*cb)(ltimer_t *, void *),  /* Callback function */
            unsigned long exp_time,              /* First expiration time interval in msec */
            unsigned long sec_exp_time,          /* Subsequent expiration time interval in msec */
            uint32_t threshold,                  /* Max num of timer expiration, 0 infinite times */
            void *user_arg,                      /* Arguments to function callback */
            bool is_backoff)                     /* Is timer backoff */
{
	ltimer_t *timer = calloc(1, sizeof(ltimer_t));
	if(timer)
	{
		memset(&timer->posix_timer, 0, sizeof(timer_t));
		assert(ltimer_get_state(timer) != TIMER_PAUSED);
		timer->cb = cb;
		timer->exp_timer = exp_time;
		timer->sec_exp_timer = sec_exp_time;
		timer->threshold = threshold;
		timer->user_arg = user_arg;
		timer->expotential_backoff = is_backoff;
		ltimer_set_state(timer, TIMER_INIT);

		/* Sanity checks */
		assert(timer->cb);

		struct sigevent evp;
		memset(&evp, 0, sizeof(struct sigevent));
		evp.sigev_value.sival_ptr = (void *)timer;
		evp.sigev_notify = SIGEV_THREAD;
		evp.sigev_notify_function = ltimer_cb_wrapper;

		int rc = timer_create(CLOCK_REALTIME, &evp, &timer->posix_timer);
		assert(rc >= 0);

		ltimer_fill_itimerspec(&timer->ts.it_value, timer->exp_timer);
		ltimer_fill_itimerspec(&timer->ts.it_interval, timer->sec_exp_timer);

		timer->exp_back_off_time = 0;
	}

	return timer;
}

/*******************************************
* ltimer_t destructor
* return:  0 - success
          -1 - failure
*******************************************/
int ltimer_delete(ltimer_t **timer)
{
	int ret = timer_delete((*timer)->posix_timer);
	if(!ret)
	{
		free(*timer);
		*timer = NULL;
	}
	else
		perror("ltimer_delete error:");
	return ret;
}


/*******************************************
* Get remaining time of the timer
* return: number of miliseconds to counter
          finish
*******************************************/
unsigned long
ltimer_get_rem_time(ltimer_t *timer)
{
	struct itimerspec remaining_time;
	memset(&remaining_time, 0, sizeof(struct itimerspec));

	/* Call unix API call to read remaining time */
	timer_gettime(timer->posix_timer, &remaining_time);

	return timespec_to_millisec(&remaining_time.it_value);
}

/*******************************************
* Pause timer counting
*******************************************/
void
ltimer_pause(ltimer_t *timer)
{
        assert(ltimer_get_state(timer) != TIMER_PAUSED);
	timer->time_remaining =
		ltimer_get_rem_time(timer);

	ltimer_fill_itimerspec(&timer->ts.it_value, 0);
	ltimer_fill_itimerspec(&timer->ts.it_interval, 0);

	ltimer_resurrect(timer);
	ltimer_set_state(timer, TIMER_PAUSED);
}

/*******************************************
* Timer resume counting
*******************************************/
void
ltimer_resume(ltimer_t *timer)
{
	assert(ltimer_get_state(timer) == TIMER_PAUSED);
	ltimer_fill_itimerspec(&timer->ts.it_value, timer->time_remaining);
        ltimer_fill_itimerspec(&timer->ts.it_interval, timer->sec_exp_timer);

        ltimer_resurrect(timer);
	ltimer_set_state(timer, TIMER_RESUMED);
}

void
ltimer_restart(ltimer_t *timer)
{
	ltimer_fill_itimerspec(&timer->ts.it_value, timer->exp_timer);
	ltimer_fill_itimerspec(&timer->ts.it_interval, timer->sec_exp_timer);

        ltimer_resurrect(timer);
        ltimer_set_state(timer, TIMER_RUNNING);
}

void
ltimer_reschedule(ltimer_t *timer, unsigned long exp_time, unsigned long sec_exp_time)
{
	timer->exp_timer = exp_time;
	timer->sec_exp_timer = sec_exp_time;

        ltimer_set_state(timer, TIMER_INIT);
}

void ltimer_cancel(ltimer_t *timer)
{
        ltimer_fill_itimerspec(&timer->ts.it_value, 0);
        ltimer_fill_itimerspec(&timer->ts.it_interval, 0);

        ltimer_resurrect(timer);
	ltimer_set_state(timer, TIMER_CANCELLED);
}
