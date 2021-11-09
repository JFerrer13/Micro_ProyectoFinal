#include "stm32f3xx.h"                  // Device header

void USART2_config (uint32_t baudrate);
void USART2_Send(uint8_t c);
void USART2_putString(char * string);
void welcomeMessage(void);
void USART2_IRQHandler (void);
void Fault(void);
