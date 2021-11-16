#include "voltaje.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "string.h"
#include "configUSART.h"

uint8_t resolucion;
char* res;
uint8_t vres_user = 0;
char *ptrAdc;
uint8_t vres = 0x01;
uint16_t lectura = 0;
uint16_t max = 0;
float voltajeIn = 0;
char bufferStr[64];

void configurar_adc(){
	//Habilito el reloj para GPIOA
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//Habilito el ADC12
	RCC->AHBENR |= RCC_AHBENR_ADC12EN;
	//Habilito el pin A7 como Analogo
	GPIOA->MODER |= (3<<14);
	//Configurar la resolución a 8bits y el OVERMODE
	ADC2->CFGR |= ADC_CFGR_OVRMOD;
	ADC2->CFGR &= ~(0x03<<3);
	ADC2->CFGR |= (vres<<3);
	//Indico que canale voy a utilizar para PA7 canal 4
	ADC2->SQR1 |= (4<<6);
	//Divido la frecuencia de reloj en 4 (HCLK/4)
	ADC1_2_COMMON->CCR |= ADC12_CCR_CKMODE;// (3<<16);
	//Habilitar ADC2
	ADC2->CR |= ADC_CR_ADEN;
}

void leerAdc(){
	res = strtok(0," ");
	vres_user = strtoul(res, &ptrAdc, 10);
	sprintf(bufferStr,"\t0x = %cv\r\n", vres_user);
	USART2_putString(bufferStr);
	if (vres_user == 6){
		vres = 0x03;
		max = 63.0f;
	} else if(vres_user == 8 || res == '\0'){
		vres_user = 0x08;
		vres = 0x02;
		max = 255.0f;
	} else if (vres_user == 10){
		vres = 0x01;
		max = 1023.0f;
	} else if (vres_user == 12){
		vres = 0x00;
		max = 4095.0f;
	} else {
		USART2_putString("Las resoluciones permitidas son 6, 8, 10 y 12 \r\n");
	}

	
	configurar_adc();
	
	lectura = leerAnalogo();
	voltajeIn = (lectura*3.3f)/max;
	
	sprintf(bufferStr,"\tv = %.4fv\r\n", voltajeIn);
	USART2_putString(bufferStr);
	sprintf(bufferStr,"\t0x = %dv\r\n", lectura);
	USART2_putString(bufferStr);
}

uint16_t leerAnalogo(void){
	volatile uint16_t valor;
	//Inicar la conversión
	ADC2->CR |= ADC_CR_ADSTART;
	//esperar que termine
	while(!(ADC2->ISR & ADC_ISR_EOC));
	//Leer la conversión
	valor = ADC2->DR;
	return valor;
}
