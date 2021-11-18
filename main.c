#include "stm32f3xx.h"                  // Device header
#include "string.h"
#include "configUSART.h"
#include "basicFunctions.h"
#include "voltaje.h"

char dato;
char string[64];
char *comando;
uint8_t indice = 0;
uint8_t nuevoComando = 0;

int main () {
	USART2_config(115200);	
	
	welcomeMessage();
	
	nuevoComando = 0;
	
	while (1){
		if (nuevoComando) {
			comando = strtok(string, " ");
			if(strcmp(comando, "RD") == 0){//-----------------Basic commands
				rd();
			} else if (strcmp(comando, "RM") == 0) {
				rm();
			} else if (strcmp(comando, "MD") == 0) {
				md();
			} else if (strcmp(comando, "MM") == 0) {
				mm();
			} else if (strcmp(comando, "BF") == 0) {
				bf();
			} else if (strcmp(comando, "RUN") == 0) {
				run();
			} else if (strcmp(comando, "CALL") == 0) {
				call();
			} else if (strcmp(comando, "H") == 0){//----------Extra comnnads
				showHelp();
			} else if (strcmp(comando, "VIN") == 0){
				leerAdc();
			} else if (strcmp(comando, "VOUT") == 0){
				colocar_voltaje();
			}else {
				unknownCommand();
			}
			USART2_putString(">> ");
			nuevoComando = 0;
		}
	}
}



void USART2_IRQHandler() {
	if(USART2->ISR & USART_ISR_RXNE){
		dato = USART2->RDR;
		
		if(dato != '\r'){
			if(dato >= 97 && dato <= 122){
				string[indice++] = dato - 32;
			} else {
				string[indice++] = dato;
			}
		}	else {
			string[indice++] = '\0';
			indice = 0;
			nuevoComando = 1;
		}
	}
}

