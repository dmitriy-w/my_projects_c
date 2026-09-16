#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

char* allocate_secret_string(const char *source, int len);
void xor_cipher(char *data, char key, int len);
void copy(char *to, const char *from);

int main() {
    int c, len = 0, clean_buffer = 0;
    char string_for_conversion[MAXLINE] = {0};
    
    printf("Введи нужный для преобразования текст: \n");
    while ((c = getchar()) != EOF) {
        string_for_conversion[len++] = c;
        if (len >= MAXLINE || c == '\n') {
            break;
        }
    }

    if (string_for_conversion[len-1] != '\n') {
        while ((c = getchar()) != '\n' && c != EOF);
    }
    string_for_conversion[len] = '\0';
    
    printf("\nВведите ключ(один символ) для шифрования: ");
    char my_key = getchar();
    while ((clean_buffer = getchar()) != '\n' && clean_buffer != EOF);

    char *data = allocate_secret_string(string_for_conversion, len);

    printf("\n\nАдрес в памяти - %p, Строка до преобразования: \n", data );
    for (int i = 0; data[i] != '\0'; i++) {
        putchar(data[i]);
    }
    
    xor_cipher(data, my_key, len);

    printf("\n\nАдрес в памяти - %p, Ваша преобразованная строка: \n", data);
    for (int i = 0; i < len; i++) {
        putchar(data[i]);
    }

    free(data);
    data = NULL;
    
    return 0;
}

char* allocate_secret_string(const char *source, int len) {
    char *a_row_in_the_heap = (char *) malloc(sizeof(char) * (len + 1));

    if (a_row_in_the_heap != NULL) {
        copy(a_row_in_the_heap, source);
    }

    return a_row_in_the_heap;
}

void xor_cipher(char *data, char key, int len) {
   for(int i = 0; i < len; i++) {
        data[i] = data[i] ^ key;
    }
}

void copy(char *to, const char *from) {
  int i = 0;

  while (from[i] != '\0') {
    to[i] = from[i];
    ++i;
  }
  to[i] = '\0';
}