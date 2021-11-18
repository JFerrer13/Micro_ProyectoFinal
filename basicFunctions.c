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

char* direccion;
char* tamanio;
char *datomm;
uint32_t tamanioi;
uint32_t direccioni;
uint32_t datommi;
uint32_t direccion_memoriamm;
char string_desplegarmm[64];

char* iniciobf;
char* finbf;
char *datobf;
char* tamaniobf;
uint32_t iniciobfi;
uint32_t finbfi;
uint32_t datobfi;
uint32_t tamaniobfi;
uint32_t direccion_memoriabfi;
char string_desplegarbfi[64];
uint8_t contadorbfi;

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
	direccion = strtok(0," ");
	datomm = strtok(0," ");
	tamanio = strtok(0," ");
	
	if(direccion[0] == '0' && direccion[1] == 'X'){
		direccioni = strtoul(direccion, &puntero, 16);
		if(datomm[0] == '0' && datomm[1] == 'X'){
			datommi = strtoul(datomm, &puntero, 16);
			
			if(tamanio == '\0'){
				tamanioi = 0x1;	
			} else {
				tamanioi = strtol(tamanio, &puntero, 10);
			}
			
			if (tamanioi == 1 || tamanioi == 2 || tamanioi == 4){
				
					switch(tamanioi)
					{
						case 1:
								cambiar_byte(direccioni, datommi);
								break;
						case 2:
								cambiar_half(direccioni, datommi);
								break;
						case 4:
								cambiar_word(direccioni, datommi);
								break;
						default:
								USART2_putString("\n El parametro size es invalido\r\n");
								break;
					}
					
					desplegar_memoria(&direccion_memoriamm,direccioni);
					sprintf(string_desplegarmm,"%d: 0x%08x - 0x%08x\r\n",1,direccioni,direccion_memoriamm);
					USART2_putString(string_desplegarmm);
					
			} else {
				USART2_putString("El parametro size debe ser 1, 2 o 4 \r\n");
			}
			
		}else{
			USART2_putString("El dato a asignar debe ser expresado en hexadecimal \r\n");
		}
	}else{
		USART2_putString("La direccion debe ser expresada en hexadecimal \r\n");
	}
	
}
void bf () {
	iniciobf = strtok(0," ");
	finbf = strtok(0, " ");
	datobf = strtok(0," ");
	tamaniobf = strtok(0," ");
	
	if(tamaniobf == '\0'){
		tamaniobfi = 0x1;	
	} else {
		tamaniobfi = strtol(tamaniobf, &puntero, 10);
	}
	
	if(iniciobf[0] == '0' && iniciobf[1] == 'X'){
		iniciobfi = strtoul(iniciobf, &puntero, 16);
		if(finbf[0] == '0' && finbf[1] == 'X'){
			finbfi = strtoul(finbf, &puntero, 16);
			if(datobf[0] == '0' && datobf[1] == 'X'){
				datobfi = strtoul(datobf, &puntero, 16);
				if(iniciobfi <= finbfi){
					if(tamaniobfi == 1 || tamaniobfi == 2 || tamaniobfi == 4){
							contadorbfi = 0;
							while(iniciobfi <= finbfi){
								switch(tamaniobfi)
								{
									case 1:
											cambiar_byte(iniciobfi, datobfi);
											break;
									case 2:
											cambiar_half(iniciobfi, datobfi);
											break;
									case 4:
											cambiar_word(iniciobfi, datobfi);
											break;
									default:
											USART2_putString("\n El parametro size es invalido\r\n");
											break;
								}
								desplegar_memoria(&direccion_memoriabfi,iniciobfi);
								sprintf(string_desplegarbfi,"%d: 0x%08x - 0x%08x\r\n",contadorbfi+1,iniciobfi,direccion_memoriabfi);
								USART2_putString(string_desplegarbfi);
								
								iniciobfi += 0x4;
								
							}
					}else{
						USART2_putString("\nel tamanio ingresado no es valido \r\n");
					}
				} else {
					USART2_putString("\nEl inicio es mayor al fin de los parametros ingresados \r\n");
				}
			}else{
				USART2_putString("El dato a insertar debe ser expresado en hexadecimal \r\n");
			}
		}else{
			USART2_putString("La direccion fin debe ser expresada en hexadecimal \r\n");
		}
	}else{
		USART2_putString("La direccion inicio debe ser expresada en hexadecimal \r\n");
	}
	
}

void run () {
  direccion = strtok(0," ");
  if(direccion[0] == '0' && direccion[1] == 'X'){
    direccioni = strtoul(direccion, &puntero, 16);
    ejecutar(direccioni);
  } else {
    USART2_putString("La direccion debe ser expresada en hexadecimal \r\n");
  }
}

void call () {
  direccion = strtok(0," ");
  if(direccion[0] == '0' && direccion[1] == 'X'){
    direccioni = strtoul(direccion, &puntero, 16);
    ir_direccion(direccioni);
  } else {
    USART2_putString("La direccion debe ser expresada en hexadecimal \r\n");
  }
}

