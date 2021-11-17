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
	USART2_putString("      {_;/   {_//  No entiendo. ¿Necesitas ayuda? escribe 'h' en la consola.\n\r\n\r");
}

void Fault() {
	USART2_putString("   |\\      _,,,---,,_\n\r");
	USART2_putString("   /,`.-'`'    -.  ;-;;,_\n\r");
	USART2_putString("  |,4-  ) )-,_..;\\ (  `'-'\n\r");
	USART2_putString(" '---''(_/--'  `-'\\_)     ERROR! Me voy a reiniciar.\n\r");
	USART2_putString("                          .....\n\r");

	reset(0x00000004);
}

void showHelp () {
	USART2_putString(" _._     _,-'""`-._\n\r");
	USART2_putString("(,-.`._,'(       |\\`-/|\n\r");
	USART2_putString("    `-.-' \\ )-`( , o o)\n\r");
	USART2_putString("          `-    \\`_`\"'- I'm helping... \n\r");
	USART2_putString("\n\r");
	USART2_putString("Esta es la lista de comandos que puedes utilizar:   \n\r");
	USART2_putString("\n\r");
	USART2_putString("COMANDOS BASICOS\n\r");
	USART2_putString("  Register Display  [RD]      Despliega el contenido de los registros del CPU.\n\r");
	USART2_putString("  Register Modify   [RM]      Modifica el contenido del registro indicado en data.\n\r");
	USART2_putString("  Memory Display    [MD]      Despliega el contenido de la memoria desde la direccion.\n\r");
	USART2_putString("  Memory Modify     [MM]      Escribir datos en la dirección de memoria especificada.\n\r");
	USART2_putString("  Block Fill        [BF]      Escribir datosen un rango de memoria especificado.\n\r");
	USART2_putString("  Run               [RUN]     Ejecutar el código ubicado en la direccion especificada.\n\r");
	USART2_putString("  Call              [CALL]    Ejecuta la subrutpuina ubicada en la direccion expecificada.\n\r");
	USART2_putString("\n\r");
	USART2_putString("COMANDOS ADICIONALES\n\r");
	USART2_putString("  I/O Map       [IOMAP]       Asigna el estado de la entrada digital a la salida digital.\n\r");
	USART2_putString("  I/O Unmap     [IOUNMAP]     Revierte todas las asignaciones de IO realizadas con IOMAP.\n\r");
	USART2_putString("  Voltage In    [VIN]         Imprime el voltaje leido de la entrada analogica.\n\r");
	USART2_putString("  Voltage Out   [VOUT]        Devuelve el voltaje indicado.\n\r");
	USART2_putString("  MultiTap      [MULTITAP]    Habilita o deshabilita el teclado matricial.\n\r");
	USART2_putString("  Arcade        [ARCADE]      Inicia el juego... espero...\n\r");
  USART2_putString("\n\r");
}
