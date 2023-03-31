/*
*
* First program when i using signals in Linux system
* From Jacob Sorber tutorial 
*/

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>


void sigHandler(int sig)
{
   write(STDOUT_FILENO, "I won't die\n", 13);
}

void sigHandler_2(int sig)
{
   int procesID;
   printf("Sigout\n");
   printf("place the PID of process which you want to kill");
   scanf("%d", &procesID);
   kill(procesID, SIGTERM);
}


int main()
{
  int i = 0;

  signal(SIGINT, sigHandler);    /*Create signal from ctrl+c */
  signal(SIGQUIT, sigHandler_2); /*Create signal from ctrl+\ */

  printf("Start process if you wish kill me, My pid is: %d", getpid());

  while(1)
  {
    printf("Wastig your pid = %d\n", getpid());
    printf("%d\n", i++);
    sleep(2);
  }

   return 0;
}



/**************************************************************
*Funtion to print main menu************************************
***************************************************************/
void printMenu(void)
{

}
