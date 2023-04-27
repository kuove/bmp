#include <stdio.h>
#include <stdint.h>

void printBytes(const void *ptr, size_t size) {
    const uint8_t *bytes = (const uint8_t *) ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X", bytes[i]);
    }
}

int main() {
    float f = 3.0f;
    uint8_t *ptr = (uint8_t *) &f;
    for (int i = sizeof(float) - 1; i >= 0; i--) {
        printBytes(&ptr[i], 1);
    }
    printf("\n");
    return 0;
}
