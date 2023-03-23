/*
*       description: Server for sockets IPC
*
*
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_NAME "/tmp/newSock"
#define BUFFER_SIZE 256
#define MAX_CLIENTS_NUM 10

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

        /* (3) listen for incoming connections
        * if there will come more than 1 connection put in the queue size = MAX_CLIENTS_NUM
        * */
        ret = listen(con_sock, MAX_CLIENTS_NUM);
        if(ret == -1)
        {
                perror("listen failed:");
                exit(EXIT_FAILURE);
        }
        while(1)
        {
                printf("(4) Waiting for incoming connections!\n");
                /* (4) accept incoming connection, blocking system call */
                int data_sock = accept(con_sock, NULL, NULL);
                if(data_sock == -1)
                {
                        perror("accept failed:");
                        exit(EXIT_FAILURE);
                }
                printf("Connection accepted!\n");

                /* (5) Sending data to client */
                sprintf(buffer, "Please send your message\n");
                ret = write(data_sock, buffer, BUFFER_SIZE);
                if(ret == -1)
                {
                        perror("write call failed:");
                        exit(EXIT_FAILURE);
                }

                /* (6) wait for packets with data, blocking system call */
                printf("(6) Waiting for data from the client\n");
                ret = read(data_sock, buffer, BUFFER_SIZE);
                if(ret == -1)
                {
                        perror("read call failed:");
                        exit(EXIT_FAILURE);
                }

                printf("Recevied data: %s\n", buffer);

                /* break connection */
                break;
        }

        /* close socket */
        close(con_sock);

        return 0;
}
