//
// Created by Bryan Herz on 08.11.22.
//

#include "VM_memory.h"

uint8_t *createMemory(int size) {
    uint8_t *memory = (uint8_t *) malloc(size * sizeof(uint8_t));
    return memory;
}

void resetMemory(uint8_t *memory, int size) {
    for (int i = 0; i < size / sizeof(uint8_t); i++) {
        memory[i] = 0;
    }
}

void printMemoryContent(uint8_t *memory, int size) {
    for (int i = 0; i < size / sizeof(uint8_t); i++) {
        printf("%hhx\n", memory[i]);
    }
}

void freeMemory(uint8_t *memory) {
    free(memory);
}