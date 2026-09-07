#include <stdio.h>
#include <stdlib.h>

int* create_dynamic_array(int size);
void parse_memory_bytes(int *array, int size);

int main() {
    int razmer = 10;
    int *ssilca = create_dynamic_array(razmer);
    parse_memory_bytes(ssilca, razmer);

    free(ssilca);
    ssilca = NULL;
}

int* create_dynamic_array(int size) {
    int *ptr = (int *) malloc(sizeof(int) * size);
    if (ptr != NULL) {
        for (int i = 0; i < size; i++) {
            ptr[i] = 1;
        }
    }
    return ptr;
}

void parse_memory_bytes(int *array, int size) {
    unsigned char *byte_ptr = (unsigned char *)array;
    for (int i = 0; i < size * 4; i++) {
        printf("Адрес байта: %p, его значение в шестнадцатеричном виде: %02X\n", (void*)&byte_ptr[i], byte_ptr[i]);
    }

}