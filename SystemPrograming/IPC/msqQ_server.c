#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <errno.h>

#define MAX_MSG 256
#define MSG_SIZE 10
#define MSG_BUFFER_SIZE (MSG_SIZE + 10)
#define PMODE 0666

int main(int argc, char ** argv)
{
        int msgQ_fd;
        char buffer[MSG_BUFFER_SIZE];

        struct mq_attr attr;
        attr.mq_maxmsg = MAX_MSG;
        attr.mq_msgsize = MSG_SIZE;
        attr.mq_flags   = 0;
        /* open message queue */
        msgQ_fd = mq_open("/my_queue", O_RDONLY | O_CREAT, PMODE, &attr);
        if(msgQ_fd == -1)
        {

                perror("server: mq_open failed: %d");
        }

        fd_set readfsd;
        while(1)
        {
                FD_ZERO(&readfsd);
                FD_SET(msgQ_fd, &readfsd);
                select(msgQ_fd + 1, &readfsd, NULL, NULL, NULL);
                if(FD_ISSET(msgQ_fd, &readfsd))
                {
                        int n = mq_receive(msgQ_fd, (char *) &buffer, MSG_BUFFER_SIZE, NULL);
                        if(n == -1)
                        {
                                perror("mq_receive error");
                        }
                        printf("Received message: %s\n", buffer);
                }
        }

        mq_close(msgQ_fd);
        mq_unlink("/my_queue");
        return 0;
}
