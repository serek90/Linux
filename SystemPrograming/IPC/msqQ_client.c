#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#define MSG_BUFFER_SIZE 100
#define PMODE 0666
int main( int argc, char ** argv)
{
        char buffer[MSG_BUFFER_SIZE];
        int msgQ_fd;

        strcpy(buffer, "First message");

        struct mq_attr attr;
        attr.mq_maxmsg = 20;
        attr.mq_msgsize = 128;
        attr.mq_flags   = 0;
        /* open message queue */
        msgQ_fd = mq_open("/myipc", O_WRONLY | O_CREAT, PMODE, &attr);
        if(msgQ_fd == -1)
        {
                perror("client: mq_open failed");
                exit(1);
        }

        /* send message */
        if(mq_send(msgQ_fd, buffer, MSG_BUFFER_SIZE /* strlen ?? */, 0) == -1)
        {
                perror("client: Not able to send message to server\n");
                exit(1);
        }
        printf("Message was sent\n");

        mq_close(msgQ_fd);

        return 0;
}
