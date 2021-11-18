#include "stm32f3xx.h"                  // Device header

//Sirve para leer el pin de entrada analoga del ADC
uint16_t leerAnalogo(void);
//Sirve para configurar el ADC que se va a utilizar, se da valor a la frecuencia
void configurar_adc(void);
//Solicita una resolucion para la configuracion del voltaje de entrada analogica
void leerAdc(void);
//Solicita una resolucion para la configuracion y un voltaje indicado.
void colocar_voltaje(void);
