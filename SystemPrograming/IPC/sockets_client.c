#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUFFER_SIZE 256
#define SOCKET_NAME "/tmp/newSock"

int main(int argc, char **argv)
{
        char buffer[BUFFER_SIZE];
        struct sockaddr_un addr;

        /* (1) create client socket */
        int client_sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if(client_sock == -1)
        {
                perror("socket init:");
                exit(EXIT_FAILURE);
        }

        printf("Socket opened!\n");

        /* Connect socket to the address */
        addr.sun_family = AF_UNIX;
        strncpy(addr.sun_path, SOCKET_NAME, sizeof(addr.sun_path) - 1);
        int ret = connect(client_sock, (const struct sockaddr*)&addr, sizeof(struct sockaddr_un));
        if(ret == -1)
        {
                perror("connect failed:");
                exit(EXIT_FAILURE);
        }
        printf("(2) Connected to the server\n");


        sleep(10);
        /* send message */
        sprintf(buffer, "Hi server, how are you?\n");
        ret = write(client_sock, buffer, BUFFER_SIZE);
        if(ret == -1)
        {
                perror("write failed:");
                exit(EXIT_FAILURE);
        }

        //sleep(1);
        /* receive message */
        ret = read(client_sock, buffer, BUFFER_SIZE);
        if(ret == -1)
        {
                perror("read failed:");
                exit(EXIT_FAILURE);
        }

        printf("received message: %s", buffer);

        sleep(1);
        /* close soecket */
        close(client_sock);
        return 0;
}
