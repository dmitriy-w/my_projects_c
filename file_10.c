#include <stdio.h>


int main() {
    int num, num_2, rez;
    int *ssilka_na_rez;

    num = 130;
    num_2 = 170;
    ssilka_na_rez = &rez;

    rez = num + num_2;
    
 

    printf("%d\n", *ssilka_na_rez);
    printf("%p", ssilka_na_rez);
}