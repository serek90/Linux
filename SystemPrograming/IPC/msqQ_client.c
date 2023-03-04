#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#define MSG_BUFFER_SIZE 30
#define PMODE 0666
int main( int argc, char ** argv)
{
        char buffer[MSG_BUFFER_SIZE];
        int msgQ_fd;

        strcpy(buffer, "First");

        struct mq_attr attr;
        attr.mq_maxmsg = 20;
        attr.mq_msgsize = 128;
        attr.mq_flags   = 0;
        /* open message queue */
        msgQ_fd = mq_open("/my_queue", O_WRONLY, 0, 0);
        if(msgQ_fd == -1)
        {
                perror("client: mq_open failed");
                exit(1);
        }

        /* sedn message */
        if(mq_send(msgQ_fd, buffer, /* MSG_BUFFER_SIZE */ strlen(buffer) + 1, 0) == -1)
        {
                perror("client: Not able to send message to server");
                exit(1);
        }
        printf("Message was sent: %s - %d\n", buffer, strlen(buffer));

        mq_close(msgQ_fd);

        return 0;
}

