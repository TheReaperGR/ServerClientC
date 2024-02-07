/*  Konstantinos Ntouros
    AM: 2022202000153
    dit20153@go.uop.gr
    ------------------------------------
    Panagiotis Leonis
    AM: 2022202000123
    dit20123@go.uop.gr
    ------------------------------------
    _____________
    Version final 1.0.0
    _____________
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>  
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>



int main(int argc, char *argv[])
{
    struct sockaddr_in server_address;

    int client_socket;
    int client_port_socket;
    int client_connect_socket;
    FILE *fp;


    /*Variables for sending the file.*/
    char buffer[10000] = {0};
    int sending;

    /*Response from server when connecting.*/
    char client_message_socket[250];
    char client_message_socket2[250];


    /*Program data checking.*/
    if((argc > 3) || (argc == 1) || (argc <= 2))
    {
        printf("Wrong Format please retry.\n");
        printf("The format must be: \n");
        printf("For Linux -> ./name_of_exetutable <ip adress> <port>.\n");
        printf("For Windows -> name_of_exetutable.exe <ip adress> <port>.\n");
        exit(1);
    }
    if(!isdigit(*argv[2]))
    {
        printf("The port must be a number!.\n");
        exit(1);
    }

    client_port_socket = atoi(argv[2]);

    printf("Client port: %d\n", client_port_socket);



    /*File for sending to server.*/
    fp = fopen("send.txt", "r");
    if(fp == NULL)
    {
        printf("There was an error opening the file!.\n");
        exit(1);

    }
    else
    {
        printf("File opened successfully.\n");
    }




    /*Socket creation.*/
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == 0)
    {
        printf("Socket hasn't been created!.\n");
        exit(1);
    }
    else
    {
        printf("Socket created successfully.\n");
    }


    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(client_port_socket);
    server_address.sin_addr.s_addr = inet_addr(argv[1]);



    /*Connect socket to server.*/
    client_connect_socket = connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(client_connect_socket == -1)
    {
        printf("Connect socket hasn't been achieved!.\n");
        exit(1);
    }
    else
    {
        printf("Connect socket has been achieved.\n");
    }


    printf("\n");
    printf("\n");
    recv(client_socket, &client_message_socket, sizeof(client_message_socket), 0);
    recv(client_socket, &client_message_socket2, sizeof(client_message_socket2), 0);
    printf("Serve's answer is: %s\n", client_message_socket);
    printf("Serve's answer is: %s\n", client_message_socket2);
    printf("\n");



    /*Sending the file with send() funcion.*/
    while(fgets(buffer, 10000, fp) != NULL)
    {
        sending = send(client_socket, buffer, sizeof(buffer), 0);
        if(sending == 1)
        {
            perror("There was an error sending the file!.\n");
            exit(1);
        }
    }

    printf("File sended successfully.\n");

    fclose(fp);
    close(client_socket);

    return 0;
}
