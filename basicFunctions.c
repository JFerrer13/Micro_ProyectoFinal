#include "basicFunctions.h"
#include "configUSART.h"
#include "stdint.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

char *puntero;
uint32_t arreglo[15];
char tmpString[64];
uint8_t i;
long numregistro;
long nuevodatodec;

char *registro;
char *nuevodato;

char* inicio;
char* fin;


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
	registro = strtok(0," ");
	nuevodato = strtok(0," ");
	
	numregistro = strtol(registro+1, &puntero, 10);
	
	nuevodatodec = strtol(nuevodato, &puntero, 10);
	
	switch(numregistro)
	{
		case 0:
				break;
		case 1:
				cambiar_r1(nuevodatodec);	
				break;
		case 2:
				cambiar_r2(nuevodatodec);	
				break;
		case 3:
				cambiar_r3(nuevodatodec);	
				break;
		case 4:
				cambiar_r4(nuevodatodec);	
				break;
		case 5:
				cambiar_r5(nuevodatodec);	
				break;
		case 6:
				cambiar_r6(nuevodatodec);	
				break;
		case 7:
				cambiar_r7(nuevodatodec);	
				break;
		case 8:
				cambiar_r8(nuevodatodec);	
				break;
		case 9:
				cambiar_r9(nuevodatodec);	
				break;
		case 10:
				cambiar_r10(nuevodatodec);	
				break;
		case 11:
				cambiar_r11(nuevodatodec);	
				break;
		case 12:
				cambiar_r12(nuevodatodec);
				break;
		default:
				USART2_putString("Registro a modificar invalido \n");
				break;
	}
	rd();
}

void md () {
	inicio = strtok(0," ");
	fin = strtok(0," ");
	
}

void mm () {

}
void bf () {

}
void run () {

}
void call () {

}
