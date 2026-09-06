#include <stdio.h>
#include <stdlib.h>

void comparison_stack_adress(int num_1, int num_2);
void comparison_heap_adress();

int main() {
    int a = 10;
    int b = 20;
    
    printf("Реальный адрес 'a' в main: %p\n", (void*)&a);
    printf("Реальный адрес 'b' в main: %p\n\n", (void*)&b);

    comparison_stack_adress(a, b);
    comparison_heap_adress();

    return 0;
}

void comparison_stack_adress(int num_1, int num_2) {
    int *ptr1 = &num_1;
    int *ptr2 = &num_2;

    printf("Смотрим на разницу в шестнадцатеричных адресах, переданных в функцию comparison_stack_adress из main, по теории они должны лежать плотно друг к другу: \n первый адрес - %p \n второй адрес - %p", ptr1, ptr2);
    
    return;
}

void comparison_heap_adress() {
    char *ptr = (char *) malloc(1);

    if (ptr != NULL) {
        *ptr = 'X';
        printf("\n\nВыводим адрес в памяти %p, значение которого имеет тип char и равняеться - %c\n", ptr, *ptr);
        free(ptr);
        ptr = NULL;
    }

    return;
}