#include <stdio.h>
#include <sys/socket.h>//will create a cpp socket programming interface
#include <arpa/inet.h>//used for establishing connection
#include <unistd.h>//it is used to address miscellaneous symbols/constants
#include <string.h>

#define PORT 8080//server port
   
int main(int argc, char const *argv[])//used to pass command line arguments
{
    int client_socket_fd, valread;
    char client_read_buffer[1024] = {0};//buffer storing client messages

    struct sockaddr_in server_addr;//server address
    server_addr.sin_family = AF_INET;//for establishing in IPC between two or more processes
    server_addr.sin_port = htons(PORT);//specifies PORT to listen on
        
    // Creating socket file descriptor (IPv4, TCP, IP)
    if ((client_socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)//socket(domain,type,protocol)
    {
        printf("\n Client: Socket creation error \n");
        return -1;
    }

       
    // Converting IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)<=0)//int inet_pton(int af, const char *src, void *dst);
    {
        printf("\nClient: Invalid address/ Address not supported \n");
        return -1;
    }
   
    // Connecting server, return 0 with success, return -1 with error
    if (connect(client_socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("\nClient: Connection Failed \n");
        return -1;
    }

    char server_ip[INET_ADDRSTRLEN]="";
    inet_ntop(AF_INET, &server_addr.sin_addr, server_ip, INET_ADDRSTRLEN);//Converts address from binary to text
    printf("Client: connected server(%s:%d). \n", server_ip, ntohs(server_addr.sin_port));//Converts to IPV4 dotted decimal notation e.g 127.0.0.8080


    // sending a message to server
    const char *hello = "Hello from client";
    send(client_socket_fd , hello , strlen(hello) , 0 );
    printf("Client: sent message: '%s'\n", hello);
    valread = read( client_socket_fd , client_read_buffer, 1024);
    printf("Client: read: '%s'\n",client_read_buffer );

    close(client_socket_fd);//Close client side 
    return 0;
}