//Richard Williams
//9/11/19
//project 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#define MAX_LEN 1024

int main(int argc, char **argv)
{
    int sock;
    struct hostent *hp;
    struct sockaddr_in server_addr, from_addr;
    socklen_t from_len;
    char buf[MAX_LEN];
    int num_bytes;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s server port\n", argv[0]);
        exit(0);
    }
    
    // create socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }
    
    // resolve server name for its IP address, etc.
    hp = gethostbyname(argv[1]);
    if (NULL == hp) {
        perror("gethostbyname");
        exit(2);
    }
    
    // build remote server addr/port
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(&server_addr.sin_addr, hp->h_addr, hp->h_length);
    server_addr.sin_port = htons(atoi(argv[2]));
    
    // send message
//------------------------------------------------------------------------------------
    num_bytes = sendto(sock, "knock!knock!\n", 13, 0,
                       (struct sockaddr *)&server_addr,
                       sizeof(server_addr));
    
    // receive message
    from_len = sizeof(from_addr);   // must set (in & out)
    num_bytes = recvfrom(sock, buf, MAX_LEN, 0,
                         (struct sockaddr *)&from_addr,
                         &from_len);
 
    write(1, buf, num_bytes);
    printf("\n");
//-------------------------------------------------------------------------------------

    // close sock to release resource
    close(sock);
       
    return 0;
}