/*
 * 01 - Process Information
 *
 * Goal:
 * Learn the basic relationship between a process and its parent.
 *
 * Concepts:
 * - PID  - Process ID
 * - PPID - Parent Process ID
 * - getpid()
 * - getppid()
 *
 * Observation:
 * The process can be inspected from another terminal using:
 *
 *     ps -p <PID> -o pid,ppid,stat,comm
 */

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    pid_t pid = getpid();
    pid_t ppid = getppid();

    printf("==============================\n");
    printf("| Process information        |\n");
    printf("==============================\n");

    printf("PID:  %d\n", pid);
    printf("PPID: %d\n", ppid);

    return 0;
}
