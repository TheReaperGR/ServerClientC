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
#include <netdb.h>




int main(int argc, char *argv[])
{
    struct sockaddr_in server_address;

    int server_socket;
    int server_port_socket;
    int server_bind_socket;
    int server_listen_socket;
    int server_accept_socket;
    FILE *fp;
    

    /*TVariables for receiveing the file.*/
    char buffer[10000];
    int stop_receiving = 1;
    int receiveing;

    /*Messages when coneecting.*/
    char server_message_socket[250] = "Welcome to PanosKostas Server!";
    char server_message_socket2[250] = "------------------------------";


    /*Program data chekcing.*/
    if((argc > 2) || (argc == 1))
    {
        printf("Wrong Format please retry.\n");
        printf("The format must be: \n");
        printf("For Linux -> ./name_of_exetutable <port>.n");
        printf("For Windows -> name_of_exetutable.exe <port>.\n");
        exit(1);
    }
    if(!isdigit(*argv[1]))
    {
        printf("The port must be a number!.\n");
        exit(1);
    }

    server_port_socket = atoi(argv[1]);

    printf("Server port: %d\n", server_port_socket);



    /*File receiving from client.*/
    fp = fopen("recv.txt", "w");
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
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == 0)
    {
        printf("Socket hasn't been created!.\n");
        exit(1);
    }
    else
    {
        printf("Socket created successfully.\n");
    }


    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port_socket);
    server_address.sin_addr.s_addr = INADDR_ANY;



    /*Bind socket to server, server_address.*/
    server_bind_socket = bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));
    if(server_bind_socket < 0)
    {
        printf("Bind socket hasn't been achieved!.\n");
        exit(1);
    }
    else
    {
        printf("Bind socket has been achieved successfully.\n");
    }



    /*Listen creation, listen in socket's port.*/
    server_listen_socket = listen(server_socket, 5);
    if(server_listen_socket < 0)
    {
        printf("Listen socket hasn't been achieved!.\n");
        exit(1);
    }
    else
    {
        printf("Listen socket has been achieved successfully.\n");
        printf("\n");
        printf("Server is listening on port: %d\n", server_port_socket);
    }



    /*Accept creation, Accept in socket's port.*/
    server_accept_socket = accept(server_socket, NULL, NULL);
    if(server_accept_socket < 0)
    {
        printf("Accept socket hasn't been achieved!.\n");
        exit(1);
    }
    else
    {
        printf("Accept socket has been achieved successfully.\n");
    }


    printf("\n");
    printf("\n");

    
    /*Send messages, send messages to client when connected.*/
    printf("Sending messages to client......\n");
    send(server_accept_socket, server_message_socket, sizeof(server_message_socket), 0);
    send(server_accept_socket, server_message_socket2, sizeof(server_message_socket2), 0);



    /*Redeiving the  file with recv() function.*/
    while(stop_receiving == 1)
    {
        receiveing = recv(server_accept_socket, buffer, 1000, 0);
        if(receiveing <= 0)
        {
            stop_receiving = 0;
        }
        fprintf(fp, "%s", buffer);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(server_socket);

    return 0;
}
