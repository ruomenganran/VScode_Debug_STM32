#include "printf_support.h"


/*
 * Arm Compiler 4/5
 */
#if   defined ( __CC_ARM )
	#pragma import(__use_no_semihosting)
/*
 * Arm Compiler 6 (armclang)
 */
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	__asm(".global __use_no_semihosting");
/*
 * Arm Compiler 4/5
 */
#elif   defined ( __GNUC__ )
	int _write(int fd, char *ptr, int len)
	{
		if (fd > 2){
			return -1;
		}
		HAL_UART_Transmit(&huart1, ptr, len, 500);
		return len;
	}
#endif

struct __FILE 
{ 
	int handle; 
};
FILE __stdout;       
void _sys_exit(int x) 
{ 
	x = x; 
}
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);
	USART1->DR = (uint8_t) ch;      
	return ch;
}



