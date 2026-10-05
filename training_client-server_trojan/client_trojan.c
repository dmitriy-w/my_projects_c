#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 1024

int main() {
    FILE *fp;
    char cmd[] = "ls -la";
    char result[BUFSIZE];

    fp = popen(cmd, "r");

    if (fp == NULL) {
        perror("error in accessing to cmd");
        exit(1);
    }




    return 0;
}