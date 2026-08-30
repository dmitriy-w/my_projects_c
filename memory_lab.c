#include <stdio.h>
#include <stdlib.h>


int main(){
    int num, *ptr, *ptr2;

    num = 25;
    ptr = &num;

    printf("сейчас адресс в стеке - %p, имеет значение - %d\n", ptr, num);

    *ptr = 35;

    printf("а теперь адресс в стеке - %p, имеет значение - %d\n", ptr, num);

    ptr2 = (int *)malloc(sizeof(int));

    if (ptr2 != NULL) {
        *ptr2 = 50;
        printf("адресс в куче - %p, имеет значение - %d\n", ptr2, *ptr2);
        free(ptr2);
        ptr2 = NULL;
    }


    return 0;
}