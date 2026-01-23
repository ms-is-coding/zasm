#ifndef MACROS_H

#define PUSH_WORD(a, b) 0x66, 0x68, (a), (b)
#define MOV_EAX_IMM32(val) 0xb8, (val) & 0xff, ((val) >> 8) & 0xff, ((val) >> 16) & 0xff, ((val) >> 24) & 0xff
#define SYSCALL 0x0f, 0x05
#define XOR_EDI 0x31, 0xff
#define NOP 0x90
#define JUMP(pos) 0xeb, (pos)

#define MOV_EDX_IMM8(val) 0xb2, (val)
#define MOV_EAX_IMM8(val) 0xb0, (val)
#define MOV_EDI_EAX 0x89, 0xc7
#define LEA_RSI_RSP 0x48, 0x8d, 0x34, 0x24

; 

#endif
