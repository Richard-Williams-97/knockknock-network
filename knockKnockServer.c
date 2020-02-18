//richard Williams
//9/11/19

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 

#define MAX_LEN     1024

int main(int argc, char **argv)
{
    int sock;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    socklen_t client_addrlen; // client address length (in and out)
    int err_code;
    int num_bytes;
    char buf[MAX_LEN];
    
    if (argc < 2) {
        fprintf(stderr, "Error, no port number provided\n");
        exit(0);
    }
    
    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
	
    // build local internet addr/port 
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    // bind the socket to local internet addr/port
    err_code = bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err_code < 0)
    {
        perror("bind");
        exit(2);
    }
    int row=0;
    while (1) {
        // client address length
        client_addrlen = sizeof(client_addr);

        num_bytes = recvfrom(sock, buf, MAX_LEN, 0,
                             (struct sockaddr *)&client_addr, &client_addrlen);
      
        write(1, buf, num_bytes);
        printf("\n");
       
        num_bytes = sendto(sock, "whos there?\n", 12, 0,
                          (struct sockaddr *)&client_addr, client_addrlen);
    }
    
    return 0;
}