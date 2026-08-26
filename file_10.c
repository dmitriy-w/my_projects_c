#include <stdio.h>


int main() {
    int num, num_2, rez;
    int *ssilka_na_rez;

    num = 130;
    num_2 = 170;
    ssilka_na_rez = &rez;

    rez = num + num_2;
    
 

    printf("Результат в адресе памяти%d\n", *ssilka_na_rez);
    printf("Сам адрес в памяти(его номер):%p\n", ssilka_na_rez);

    *ssilka_na_rez = 500;

    printf("Значение rez после изменения через указатель: %d\n", rez);
}