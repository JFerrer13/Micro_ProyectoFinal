#include "basicFunctions.h"
#include "configUSART.h"
#include "stdint.h"
#include "stdio.h"
#include <string.h>
#include <stdlib.h>

char *puntero;
uint32_t arreglo[15];
char tmpString[64];
uint8_t contador;
long numregistro;
long nuevodatodec;
uint32_t direccion_memoria;
char string_desplegar[64];

char *registro;
char *nuevodato;

char* iniciochar;
char* finchar;
uint32_t inicio;
uint32_t fin;

void rd () {
	registers_to_array(arreglo);
	contador = 0;
	while(contador <= 14){
		sprintf(tmpString,"R%d = 0x%08x\r\n",contador,arreglo[contador]);
		USART2_putString(tmpString);
		contador++;
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
				USART2_putString("\nRegistro a modificar invalido \n");
				break;
	}
	rd();
}

void md () {
	iniciochar = strtok(0," ");
	finchar = strtok(0," ");
	
	if(iniciochar == '\0'){
		inicio = strtoul("0x20000000", &puntero, 16);
	}else{
		if(iniciochar[0] == '0' && iniciochar[1] == 'X'){
			inicio = strtoul(iniciochar, &puntero, 16);
		}else{
			USART2_putString("El parametro inicio debe ingresarlo en hexadecimal \r\n");
		}
	}
	
	if(finchar == '\0'){
		fin = inicio;
		fin += 10*4;
	}else{
		if(finchar[0] == '0' && finchar[1] == 'X'){
			fin = strtoul(finchar, &puntero, 16);
		}else{
			USART2_putString("\nEl parametro fin debe ingresarlo en hexadecimal \r\n");
		}
	}
	
	if(inicio <= fin){
		contador = 0;
		while(inicio <= fin){
			desplegar_memoria(&direccion_memoria,inicio);
			sprintf(string_desplegar,"%d: 0x%08x - 0x%08x\r\n",contador+1,inicio,direccion_memoria);
			USART2_putString(string_desplegar);
			contador++;
			inicio += 0x4;
		}
	} else {
		USART2_putString("\nEl inicio es mayor al fin de los parametros ingresados \r\n");
	}
}

void mm () {

}
void bf () {

}
void run () {

}
void call () {

}
