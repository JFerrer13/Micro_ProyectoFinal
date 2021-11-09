#include "configUSART.h"

char dato;
char comando[64];
uint8_t indice = 0;

void USART2_IRQHandler() {
	if(USART2->ISR & USART_ISR_RXNE){
		dato = USART2->RDR;
		
		if(dato != '\r'){
			comando[indice++] = dato;
		}	else {
			comando[indice++] = '\0';
			indice = 0;
			USART2_putString("\n\r>> ");
		}
	}
}

void USART2_config(uint32_t baudrate) {
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	
	GPIOA->MODER |= (0x02<<4) | (0x02<<30);
	GPIOA->AFR [0] |= (0x07<<8);
	GPIOA->AFR [1] |= (0x07<<28);
	
	USART2->BRR = (uint32_t)(SystemCoreClock/baudrate);
	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE;
	USART2->CR1 |= USART_CR1_UE;
	USART2->CR1 |= USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART2_IRQn);
}

void USART2_Send(uint8_t c){
	while (!(USART2->ISR & USART_ISR_TC));
	USART2->TDR = c;
}

void USART2_putString(char * string){
	while(*string){
		USART2_Send(*string);
		string++;
	}
}
void welcomeMessage () {
	USART2_putString("\n\n\r");
	USART2_putString(" ) \n\r");
	USART2_putString("(        /( \n\r");
	USART2_putString(" \\yYYy,_I_`; \n\r");
	USART2_putString(" JgLFO^JL_ \n\r");
	USART2_putString(" \\ `-  \\, ` PROYECTO FINAL  \n\r");
	USART2_putString("  `  \n\r");
	USART2_putString("INTEGRANTES:  \n\r");
	USART2_putString("\t 15006597 - Kevin Axpuac  \n\r");
	USART2_putString("\t 13001762 - Edy Cocon  \n\r");
	USART2_putString("\t 13000522 - Javier Ferrer  \n\r");
	USART2_putString("\n\r");
	USART2_putString("HARDWARE  \n\r");
	USART2_putString("\t I'm runnig over a STMF303k8t6  \n\r");
	USART2_putString("\n\r");
	USART2_putString("\t If you need help type '--help' or '--h' to read the documentation   \n\r");
	USART2_putString("\n\r");
	USART2_putString("\n\r");
	
	USART2_putString(">> ");
}
void Fault() {
	USART2_putString("FAULT  \n\r");
	USART2_putString("Vamos a reiniciar el programa.  \n\r");
	USART2_putString("...  \n\r");
}
