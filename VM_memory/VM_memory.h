//
// Created by Bryan Herz on 08.11.22.
//
#pragma once
#ifndef GREYVM_C_VM_MEMORY_H
#define GREYVM_C_VM_MEMORY_H

#endif //GREYVM_C_VM_MEMORY_H

#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"

uint8_t *createMemory(int size);

void freeMemory(uint8_t *memory);

void resetMemory(uint8_t *memory, int size);

void printMemoryContent(uint8_t *memory, int size);
