#include "basicFunctions.h"
#include "configUSART.h"
#include "stdint.h"
#include "stdio.h"

uint32_t arreglo[15];
char tmpString[64];
uint8_t i;

void rd () {
	registers_to_array(arreglo);
	i = 0;
	while(i <= 14){
		sprintf(tmpString,"R%d = 0x%08x\r\n",i,arreglo[i]);
		USART2_putString(tmpString);
		i++;
	}
}
void rm () {

}
void md () {

}
void mm () {

}
void bf () {

}
void run () {

}
void call () {

}
