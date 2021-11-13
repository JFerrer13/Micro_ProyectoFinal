#include "configUSART.h"

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
	USART2_putString("\t I'm runnig over a STMF303k8t6\n\r");
	USART2_putString("\n\r");
	USART2_putString("\t If you need help type 'h' for some help\n\r");
	USART2_putString("\n\r");
	USART2_putString("\n\r");
	
	USART2_putString(">> ");
}

void unknownCommand() {
	USART2_putString("                   _..\n\r");
	USART2_putString("  /}_{\\           /.-'\n\r");
	USART2_putString(" ( a a )-.___...-'/\n\r");
	USART2_putString(" ==._.==         ;\n\r");
	USART2_putString("      \\ i _..._ /,\n\r");
	USART2_putString("      {_;/   {_//  Unknown command. Do you need help? type 'h' for help.\n\r\n\r");
}

void Fault() {
	USART2_putString("   |\\      _,,,---,,_\n\r");
	USART2_putString("   /,`.-'`'    -.  ;-;;,_\n\r");
	USART2_putString("  |,4-  ) )-,_..;\\ (  `'-'\n\r");
	USART2_putString(" '---''(_/--'  `-'\\_)     FAULT! I'm restarting, please wait.\n\r");
	USART2_putString("                          .....\n\r");
}

void showHelp () {
	USART2_putString("      _._     _,-'""`-._\n\r");
	USART2_putString("     (,-.`._,'(       |\\`-/|\n\r");
	USART2_putString("         `-.-' \\ )-`( , o o)\n\r");
	USART2_putString("               `-    \\`_`\"'- I'm helping... \n\r");
}
