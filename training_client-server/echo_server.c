#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
    int listenfd, connfd; //listenfd - это слушающий сокет (дескриптор), connfd - это присоединённый сокет
    socklen_t clilen; //размер структуры адреса клиента
    struct sockaddr_in cliaddr, servaddr; //servaddr — это настройки адреса сервера (какой порт слушать),  cliaddr - это IP-адрес и порт клиента

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0) {
        perror("Ошибка - не получилось создать socket");
        exit(1);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //32-разрядный адрес ipv4
    servaddr.sin_port = htons(4444); //16-разрядный номер порта ТСР

    int bind_status = bind(listenfd, (const struct sockaddr *) &servaddr, sizeof(servaddr));
    if (bind_status < 0) {
        perror("Ошибка в bind");
        exit(1);
    }

    return 0;
}