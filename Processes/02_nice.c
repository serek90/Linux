/*
 * 02 - Process Priority
 *
 * Goal:
 * Learn how to read and change the nice value of a process.
 *
 * Concepts:
 * - getpriority()
 * - setpriority()
 * - nice value
 * - errno
 * - process permissions
 *
 * Experiment:
 * Change the value of `new_priority` and observe the result.
 *
 * Try different values in the range:
 *
 *     -19 ... 0 ... +19
 *
 * You can also try -20, which is the minimum allowed nice value
 * on Linux, but setting negative nice values usually requires
 * additional privileges.
 *
 * Observe the result using:
 *
 *     ps -p <PID> -o pid,ppid,ni,pri,stat,comm
 */

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>

int main(void)
{
    pid_t pid = getpid();

    printf("==============================\n");
    printf("| Process priority           |\n");
    printf("==============================\n");

    printf("PID: %d\n", pid);

    errno = 0;
    int current_nice = getpriority(PRIO_PROCESS, pid);

    if (errno != 0) {
        perror("getpriority");
        return 1;
    }

    printf("Current nice value: %d\n", current_nice);

    int new_nice = 10;

    printf("Trying to set nice value to: %d\n", new_nice);

    if (setpriority(PRIO_PROCESS, pid, new_nice) == -1) {
        perror("setpriority");
        return 1;
    }

    errno = 0;
    current_nice = getpriority(PRIO_PROCESS, pid);

    if (errno != 0) {
        perror("getpriority");
        return 1;
    }

    printf("New nice value: %d\n", current_nice);

    return 0;
}
