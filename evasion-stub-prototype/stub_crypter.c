#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void execute_in_memory(const unsigned char *encrypted_data, int len, unsigned char key);

#define XOR_KEY 0x5A

const unsigned char encrypted_payload[] = {
    0x0E, 0x1B, 0x08, 0x1D, 0x1F, 0x0E, 0x05, 0x17, 
    0x1B, 0x16, 0x0D, 0x1B, 0x08, 0x1F, 0x05, 0x19, 
    0x15, 0x14, 0x14, 0x1F, 0x19, 0x0E, 0x1F, 0x1E
};



int main() {
    const int payload_len = sizeof(encrypted_payload) / sizeof(encrypted_payload[0]);
    printf("Стаб запущен.\n");
    printf("Сканирование диска...\n");
    printf("Вирусов не найдено.\n");

    execute_in_memory(encrypted_payload, payload_len, XOR_KEY);

    return 0;
}

void execute_in_memory(const unsigned char *encrypted_data, int len, unsigned char key) {
    char *memory_for_payload = (char *) malloc(sizeof(char) * (len + 1));

    if (memory_for_payload != NULL) {
        for (int i = 0; i < len; i++) {
            memory_for_payload[i] = encrypted_data[i] ^ key;
        }
        memory_for_payload[len] = '\0';
        for (int i = 0; memory_for_payload[i] != '\0'; i++) {
            putchar(memory_for_payload[i]);
        }
    }

    memset(memory_for_payload, 0, len + 1);
    free(memory_for_payload);
    memory_for_payload = NULL;
}