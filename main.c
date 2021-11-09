#include "stm32f3xx.h"                  // Device header
#include "configUSART.h"

int main () {
	USART2_config(115200);	
	
	welcomeMessage();
	
	while (1){
		
	}
}


