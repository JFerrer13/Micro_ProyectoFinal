#include "stm32f3xx.h"                  // Device header
//Guarda los registros en el arreglo.
extern void registers_to_array(uint32_t *registros);
//cambia el valor de R1
extern void cambiar_r1(uint32_t dato);
//cambia el valor de R2
extern void cambiar_r2(uint32_t dato);
//cambia el valor de R3
extern void cambiar_r3(uint32_t dato);
//cambia el valor de R4
extern void cambiar_r4(uint32_t dato);
//cambia el valor de R5
extern void cambiar_r5(uint32_t dato);
//cambia el valor de R6
extern void cambiar_r6(uint32_t dato);
//cambia el valor de R7
extern void cambiar_r7(uint32_t dato);
//cambia el valor de R8
extern void cambiar_r8(uint32_t dato);
//cambia el valor de R9
extern void cambiar_r9(uint32_t dato);
//cambia el valor de R10
extern void cambiar_r10(uint32_t dato);
//cambia el valor de R11
extern void cambiar_r11(uint32_t dato);
//cambia el valor de R12
extern void cambiar_r12(uint32_t dato);
//Desplie obtenemos la referencia el valor de lo que contiene la memoria en la direccion. 
extern void desplegar_memoria(uint32_t *reg_memoria, uint32_t vinicio);
//Set de un byte (8 bits) a una direccion de memoria
extern void cambiar_byte(uint32_t direccion, uint32_t dato);
//Set de un half-word (16 bits) a una direccion de memoria
extern void cambiar_half(uint32_t direccion, uint32_t dato);
//Set de un word (32 bits) a una direccion de memoria
extern void cambiar_word(uint32_t direccion, uint32_t dato);
//salto a una direccion de memoria
extern void ir_direccion(uint32_t direccion);
//salta a la ejecucion de una subrutina
extern void ejecutar(uint32_t direccion);

//despliega los registros
void rd (void);
//Cambia el valor a un registro, parametros obtenidos en el string tokenizado: Registro, valor
void rm (void);
//Despliega el valor de la memoria de acuerdo a un rango: Inicio, Final.
void md (void);
//Cambia el valor de un espacio de memoria enviado, parametros: direccion, dato y tamanio del dato.
void mm (void);
//Cambia el valor de un rango de espacio de memoria enviado, parametros: direccion inicial, direccion final, dato y tamanio del dato.
void bf (void);
//Ejecuta el codigo ubicado en la direccion enviada, parametro: direccion de memoria. 
void run (void);
//Ejecuta la subrutina de acuerdo a la direccion de memoria enviada.
void call (void);
