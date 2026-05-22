#include "uart.h"
void USART2_Init(void){
RCC -> APB1ENR |=0x20000;
RCC ->AHB1ENR |=0x01;
GPIOA->MODER &= ~0x00F0;   // clear PA2, PA3 mode bits
GPIOA->MODER |=  0x00A0;   // set alternate function mode

GPIOA->AFR[0] &= ~0xFF00;  // clear AF bits
GPIOA->AFR[0] |=  0x7700;  // AF7 = USART2
USART2->BRR = 0x0683;   // 9600 baud @16MHz
USART2->CR1 |= 0x000C;  // enable transmitter
USART2 ->CR2 =0x000;
USART2 ->CR3 =0x000;
USART2->CR1 |= 0x2000;  // enable USART
	
	

}
int USART2_write(int ch)
{
    while (!(USART2->SR & 0x0080))
    {
    }

    USART2->DR = (ch & 0xFF);

    return ch;
}

int USART2_read(void)
{
    while (!(USART2->SR & 0x0020))
    {
    }

    return USART2->DR;
}

int fgetc(FILE *f){
	(void)f;
    int c;

    c = USART2_read();

    if (c == '\r')
    {
        USART2_write(c);
        c = '\n';
    }

    USART2_write(c);

    return c;
}
/* Called by C library console/file output */

int fputc(int c, FILE *f)
{
	(void)f;
    return USART2_write(c);   /* write the character to console */
}
int n;
char str[80];

void test_setup(void)
{
    printf("please enter a number: ");
    scanf("%d", &n);
    printf("the number entered is: %d\r\n", n);
    printf("please type a character string: ");
    gets(str);
    printf("the character string entered is: ");
    puts(str);
    printf("\r\n");
}

