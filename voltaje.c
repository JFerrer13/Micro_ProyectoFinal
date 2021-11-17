#include "voltaje.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "configUSART.h"

char* 		aux;
char			bufferStr[64];
float 		voltajeIn;
uint8_t 	operar;
uint8_t 	resolucion;
uint8_t 	confResolucion;
uint16_t 	max;
uint16_t 	lectura;
uint32_t	voltajeOut;

char*			voltaje;

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
	operar = 1;

	switch(resolucion) 
	{
		case 0:
			resolucion = 0x08;
			confResolucion = 0x02;
			max = 255.0f;
			break;
		case 6:
			confResolucion = 0x03;
			max = 63.0f;
			break;
		case 8:
			resolucion = 0x08;
			confResolucion = 0x02;
			max = 255.0f;
			break;
		case 10:
			confResolucion = 0x01;
			max = 1023.0f;
			break;
		case 12:
			confResolucion = 0x00;
			max = 4095.0f;
			break;
		default:
			operar = 0;
			USART2_putString("Las resoluciones permitidas son 6, 8, 10 y 12. NULL/0 para el caso base(8). \r\n");
			break;
	}
	
	if(operar)
	{
		configurar_adc();
		
		lectura = leerAnalogo();
		voltajeIn = (lectura*3.3f)/max;	
		
		sprintf(bufferStr,"\tv = %.4fv\r\n\tCon resolucion: %d\r\n\tProporcional: 0x%d\r\n", voltajeIn, resolucion, lectura);
		USART2_putString(bufferStr);
	}
}

void colocar_voltaje() {
	voltaje = strtok(NULL," ");
	resolucion = strtoul(strtok(NULL," "), &aux, 10);
	operar = 1;
	
	switch(resolucion) 
	{
		case 0:
			max = 255.0f;
			break;
		case 8:
			max = 255.0f;
			break;
		case 12:
			max = 4095.0f;
			break;
		default:
			operar = 0;
			USART2_putString("Las resoluciones permitidas son 8 y 12. NULL/0 para el caso base(8). \r\n");
			break;
	}
	
	if(operar)
	{
		RCC->APB1ENR |= RCC_APB1ENR_DAC2EN;
		GPIOA->MODER |= (3<<12);
		DAC2->CR |= DAC_CR_EN1;
		DAC2->CR |= DAC_CR_OUTEN1;
		lectura = ((strtof(voltaje, &aux)/4.5f) * max)+0.5f;
		if(resolucion == 12){
			DAC2->DHR12R1 = ((strtof(voltaje, &aux)/4.5f) * max)+0.5f;
		} else {
			DAC2->DHR8R1 = ((strtof(voltaje, &aux)/4.5f) * max)+0.5f;
		}
		
		sprintf(bufferStr,"\tv_out = %sv\r\n\tCon resolucion: %d\r\n\tProporcional: 0x%d\r\n", voltaje, resolucion, lectura);
		USART2_putString(bufferStr);
	}
}

uint16_t leerAnalogo(void){
	volatile uint16_t valor;
	ADC2->CR |= ADC_CR_ADSTART;
	while(!(ADC2->ISR & ADC_ISR_EOC));
	valor = ADC2->DR;
	return valor;
}
