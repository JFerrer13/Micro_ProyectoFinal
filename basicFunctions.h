#include "stm32f3xx.h"                  // Device header

extern void registers_to_array(uint32_t *registros);
extern void cambiar_r1(uint32_t dato);
extern void cambiar_r3(uint32_t dato);
extern void cambiar_r4(uint32_t dato);
extern void cambiar_r5(uint32_t dato);
extern void cambiar_r6(uint32_t dato);
extern void cambiar_r7(uint32_t dato);
extern void cambiar_r8(uint32_t dato);
extern void cambiar_r9(uint32_t dato);
extern void cambiar_r10(uint32_t dato);
extern void cambiar_r11(uint32_t dato);
extern void cambiar_r12(uint32_t dato);


void rd (void);
void rm (void);
void md (void);
void mm (void);
void bf (void);
void run (void);
void call (void);
