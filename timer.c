#include "LPC11xx.h"                    // Device header

#define  LED1_ON()  (LPC_GPIO2 -> DATA &=~(1<<0))   
#define  LED1_OFF()  (LPC_GPIO2-> DATA |=  (1<<0))  
#define  LED2_ON()  (LPC_GPIO2 -> DATA &=~(1<<1))  
#define  LED2_OFF()  (LPC_GPIO2-> DATA |=  (1<<1)) 
#define  LED3_ON()  (LPC_GPIO2 -> DATA &=~(1<<2))   
#define  LED3_OFF()  (LPC_GPIO2-> DATA |=  (1<<2))  
#define  LED4_ON()  (LPC_GPIO2 -> DATA &=~(1<<3))  
#define  LED4_OFF()  (LPC_GPIO2-> DATA |=  (1<<3))
unsigned int status;
static volatile unsigned int ticks=0;
void delay(void)
{
		uint16_t i,j;
  
		for(i=0;i<5000;i++)
     for(j=0;j<500;j++);
}

void  LedInit()
{
		LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);   
		LPC_IOCON->PIO2_0  &=  ~0x07;
		LPC_IOCON->PIO2_0 |= 0x00;  
		LPC_IOCON->PIO2_1  &=  ~0x07;
		LPC_IOCON->PIO2_1 |= 0x00;  
		LPC_IOCON->PIO2_2  &=  ~0x07;
		LPC_IOCON->PIO2_2 |= 0x00;
		LPC_IOCON->PIO2_3  &=  ~0x07;
		LPC_IOCON->PIO2_3 |= 0x00;	
	
    LPC_SYSCON->SYSAHBCLKCTRL  &=  ~(1<<16);
    LPC_SYSCON->SYSAHBCLKCTRL  |=  (1<<6);
    LPC_GPIO2->DIR  |=(1<<0);  
    LPC_GPIO2->DATA  |= (1<<0);   
    LPC_GPIO2->DIR  |=(1<<1);  
    LPC_GPIO2->DATA  |= (1<<1);
		LPC_GPIO2->DIR  |=(1<<2);  
    LPC_GPIO2->DATA  |= (1<<2); 
		LPC_GPIO2->DIR  |=(1<<3);  
    LPC_GPIO2->DATA  |= (1<<3);  	
}


void TIMER32_0_IRQHandler(void)
{
	uint16_t i,j;
   LPC_TMR32B0->IR =0x01;
	 for(i=0;i<3;i++)
	{
	 LED1_ON();
	 delay();
	 LED1_OFF();
	 LED2_ON();
	 delay();
	 LED2_OFF();
   LED3_ON();
	 delay();
   LED3_OFF();
	 LED4_ON();
	 delay();
	 LED4_OFF();}
	for(j=0;j<3;j++){
	 LED4_ON();
	 delay();
	 LED4_OFF();
	 LED3_ON();
	 delay();
	 LED3_OFF();
   LED2_ON();
	 delay();
   LED2_OFF();
	 LED1_ON();
	 delay();
	 LED1_OFF();
	}

}



void Timer0Init(void)
{
  LPC_SYSCON->SYSAHBCLKCTRL  |=(1<<9);
	LPC_TMR32B0->IR =0x01;  
	LPC_TMR32B0->PR=0; 
	LPC_TMR32B0->MCR =0x03;//?tc?????
	LPC_TMR32B0->MR0=2500000;//??tc
	LPC_TMR32B0->TCR=0x01;
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
}



int main(void)
{
LedInit();
Timer0Init();
while(1)
{

	 }
  
}
	