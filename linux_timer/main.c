/*
 *	Program to test ltimer API
 *
 *
 *
 */

#include "timerlib.h"
#include <stdio.h>

void user_def_cb(ltimer_t *timer, void *user_data)
{
	printf("Counter count, user data is: %s\n", (char *)user_data);
}

int main()
{
	char *name = "JAKUB";
	ltimer_t *timer = ltimer_setup(user_def_cb, 10000, 10000, 0, name, false);
	ltimer_start(timer);

	/* Priniting menu */
	printf("1. Pause timer\n");
	printf("2. Resume timer\n");
	printf("3. Restart timer\n");
	printf("4. Reschedule timer\n");
	printf("5. Delete timer\n");
	printf("6. Cancel timer\n");
	printf("7. Get remaining time\n");
	printf("8. Print timer state\n");

	char choice;
	while(1)
	{
		choice = getchar();
		switch(choice)
		{
			case '1':
				ltimer_pause(timer);
				printf("Timer pause\n");
				break;
			case '2':
				ltimer_resume(timer);
				break;
			case '3':
				ltimer_restart(timer);
				break;
			case '4':
				ltimer_reschedule(timer,
				                  20000,
                                                  20000);
				break;
			case '5':
				if(!ltimer_delete(&timer))
				{
					printf("Timer was deleted\n");
					return 0;
				}
				break;
			case '6':
				ltimer_cancel(timer);
				break;
			case '7':
				printf("Remaining time %d",
				       ltimer_get_rem_time(timer));
				break;
			case '8':
				ltimer_get_state(timer);
				break;
		}


	}
	pause();
	return 0;
}
