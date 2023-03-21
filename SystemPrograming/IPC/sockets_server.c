#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/newSock"
#define BUFFER_SIZE 256

int main(int argc, char **argv)
{

        struct sockaddr_un sock_name;
        char buffer[BUFFER_SIZE];

        /* remove old socket if needed */
        unlink(SOCKET_NAME);

        /* (1) Master socket creation */
        int con_sock = socket(AF_UNIX, SOCK_STREAM, 0);
        if(con_sock == -1)
        {
                perror("socket creation:");
                exit(EXIT_FAILURE);
        }
        printf("(1) Master socket created!\n");

        /* initialize */
        memset(&sock_name, 0, sizeof(struct sockaddr_un));
        sock_name.sun_family = AF_UNIX;
        strncpy(sock_name.sun_path, SOCKET_NAME, sizeof(sock_name.sun_path) - 1);

        /* (2) Bind socket to the socket name */
        int ret = bind(con_sock, (const struct sockaddr *)&sock_name, sizeof(struct sockaddr_un));
        if(ret == -1)
        {
                perror("bind:");
                exit(EXIT_FAILURE);
        }
        printf("(2) binding succes!\n");

        while(1)
        {
                printf("(3) Waiting for incoming connections!\n");
        }
        return 0;
}
