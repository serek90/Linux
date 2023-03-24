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

/****************************************
* file descriptors array and its operations
****************************************/
int monitored_fd[MAX_CLIENTS_NUM];

void monitored_fd_init()
{
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
                monitored_fd[i] = -1;
}

void monitored_fd_add(int act_fd)
{
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
        {
                if(monitored_fd[i] == -1)
                {
                        monitored_fd[i] = act_fd;
                        return;
                }
        }
}

void monitored_fd_rm(int fd)
{
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
        {
                if(monitored_fd[i] == fd)
                {
                        monitored_fd[i] = -1;
                        return;
                }
        }
}

/* Find the client which has sent th data req */
int monitored_fd_get(fd_set *ptr)
{
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
        {
                if(FD_ISSET(monitored_fd[i], ptr))
                        return monitored_fd[i];
        }
}

void refresh_fd_set(fd_set *ptr)
{
        /* clear */
        FD_ZERO(ptr);
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
        {
                if(monitored_fd[i] != -1)
                        FD_SET(monitored_fd[i], ptr);
        }
}

int get_max_fd()
{
        int max = -1;
        for(int i = 0; i < MAX_CLIENTS_NUM; i++)
                max = monitored_fd[i] > max ? monitored_fd[i] : max;

        return max;
}

/******************************************
*main function
*******************************************/
int main(int argc, char **argv)
{

        struct sockaddr_un sock_name;
        char buffer[BUFFER_SIZE];
        fd_set read_fds;
        monitored_fd_init();

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

        /* add master socket fd to monitored_fd array */
        monitored_fd_add(con_sock);

        while(1)
        {
                /* copy everything from monitored_fd to read_fds */
                refresh_fd_set(&read_fds);
                select(get_max_fd() + 1, &read_fds, NULL, NULL, NULL);

                /* new connection arrived */
                if(FD_ISSET(con_sock, &read_fds))
                {

                        /* (4) accept incoming connection, blocking system call */
                        int data_sock = accept(con_sock, NULL, NULL);
                        if(data_sock == -1)
                        {
                                perror("accept failed:");
                                exit(EXIT_FAILURE);
                        }
                        printf("New connection accepted!\n");
                        monitored_fd_add(data_sock);
                }
                else /* data arrived on the other client file desc */
                {
                        /* Find the client which has sent th data req */
                        int data_socket = monitored_fd_get(&read_fds);

                        /* (6) wait for packets with data, blocking system call */
                        printf("(6) Waiting for data from the client\n");
                        ret = read(data_socket, buffer, BUFFER_SIZE);
                        if(ret == -1)
                        {
                                perror("read call failed:");
                                exit(EXIT_FAILURE);
                        }

                        printf("Recevied data: %s\n", buffer);


                        /* (5) Sending data to client */
                        memset(buffer, 0, BUFFER_SIZE);
                        sprintf(buffer, "I'm fine!\n");
                        ret = write(data_socket, buffer, BUFFER_SIZE);
                        if(ret == -1)
                        {
                                perror("write call failed:");
                                exit(EXIT_FAILURE);
                        }

                        /*close connectection */
                        close(data_socket);
                        monitored_fd_rm(data_socket);
                }
        }

        /* close the master socket */
        close(con_sock);
        printf("Master socket connection closed\n");
        /* released resources */
        unlink(SOCKET_NAME);

        return 0;
}
