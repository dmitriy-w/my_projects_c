#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#define MAXLINE 1024


int main() {
    int sockfd; // дескриптор сокета через который будем стучаться в сервер
    struct sockaddr_in servaddr; //структура сервера к которому будем стучаться
    char buf[MAXLINE]; //буфер под ответ сервера
    ssize_t n; //длина переданного текста

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Ошибка в создании клиентского сокета");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr)); 
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr); //запись 32 разрядного ip адреса в структуру 
    servaddr.sin_family = AF_INET; //семейство версии ip адресов
    servaddr.sin_port = htons(4444); //порт TCP
    
    int connect_status = connect(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if (connect_status < 0) {
        perror("ошибка в функции connect");
        exit(1);
    }

    while(1) {
        printf("Вы: ");

        fgets(buf, MAXLINE, stdin);//ожидание ввода текста и его запись в буфер
        write(sockfd, buf, strlen(buf));
        n = read(sockfd, buf, MAXLINE);
        if (n <= 0) break;
        buf[n] = '\0';

        printf("\nОтвет сервера: %s\n", buf);
    }

    close(sockfd);

    return 0;
}