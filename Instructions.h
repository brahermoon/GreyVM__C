//
// Created by Bryan Herz on 08.11.22.
//
#pragma once
#ifndef GREYVM_C_INSTRUCTIONS_H
#define GREYVM_C_INSTRUCTIONS_H

#endif //GREYVM_C_INSTRUCTIONS_H

#include "stdint.h"

//this enum is responsible for the right opcodes for the asm in binary. It helps you code properly too!
typedef enum {
    MOV_LIT_REG_OP,
    MOV_REG_REG_OP,
    MOV_LIT_MEM_OP,
    MOV_REG_MEM_OP,
    MOV_MEM_REG_OP,
    MOV_MEM_MEM_OP,
    ADD_LIT_REG_OP,
    ADD_REG_REG_OP,
    HLT_OP,
    DBG_OP
} Instructions;