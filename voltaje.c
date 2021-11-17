#include "voltaje.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "configUSART.h"

uint8_t resolucion;
char *aux;
uint8_t confResolucion;
uint16_t lectura;
uint16_t max;
float voltajeIn;
char bufferStr[64];

void configurar_adc(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	GPIOA->MODER |= (3<<14);
	ADC2->CFGR |= ADC_CFGR_OVRMOD;
	ADC2->CFGR &= ~(0x03<<3);
	ADC2->CFGR |= (confResolucion<<3);
	ADC2->SQR1 |= (4<<6);
	ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE;
	ADC2->CR |= ADC_CR_ADEN;
}

void leerAdc(){
	resolucion = strtoul(strtok(NULL," "), &aux, 10);

	if (resolucion == 6){
		confResolucion = 0x03;
		max = 63.0f;
	} else if(resolucion == 8 || resolucion == 0){
		resolucion = 0x08;
		confResolucion = 0x02;
		max = 255.0f;
	} else if (resolucion == 10){
		confResolucion = 0x01;
		max = 1023.0f;
	} else if (resolucion == 12){
		confResolucion = 0x00;
		max = 4095.0f;
	} else {
		USART2_putString("Las resoluciones permitidas son 6, 8, 10 y 12. NULL/0 para el caso base. \r\n");
	}
	
	configurar_adc();
	
	lectura = leerAnalogo();
	voltajeIn = (lectura*3.3f)/max;	
	
	sprintf(bufferStr,"\tv = %.4fv\r\n\tCon resolucion: %d\r\n\tProporcional: 0x%d\r\n", voltajeIn,resolucion,lectura);
	USART2_putString(bufferStr);
}

uint16_t leerAnalogo(void){
	volatile uint16_t valor;
	ADC2->CR |= ADC_CR_ADSTART;
	while(!(ADC2->ISR & ADC_ISR_EOC));
	valor = ADC2->DR;
	return valor;
}
