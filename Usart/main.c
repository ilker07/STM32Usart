#include "stm32f10x.h"                  // Device header
#include "delay.h" 



uint8_t gelen_veri;
uint8_t i=0;

void usart_init()
{
	
  USART1->CR1 |=1<<13;//UE biti.
	USART1->CR1 |=1<<2; //RE enable.
	USART1->CR1  |=1<<3;//Transmitter enable.
  USART1->CR1   &= ~(1<<12); // 8 BIT.
	USART1 ->BRR  =0x341;//9600 baud rate.
	USART1 ->CR2  &= ~(1<<12);//1 STOP BITI.
	USART1 ->CR2  &= ~(1<<13);//1 STOP BITI.
	USART1->CR3  &=~(1<<9); //HARDWARE FLOW YOK. CTSE
	USART1->CR3  &=~(1<<8);//HARDWARE FLOW YOK.RTSE
	
}

void veri_yolla(uint8_t veri)
{
	while( !(USART1->SR & (1<<6)));//TC=1 olana kadar bekle.
	USART1->DR =veri;
	
}
uint8_t veri_al()
{
	
  while(!(USART1->SR &(1<<5)));//1 OLANA KADAR BEKLE.
	return USART1->DR;
}


int main()
	
{
	
	//pa9 usart1 tx
	//pa10 rx floating input.4 degerini alir 0100
	
	
	RCC->APB2ENR |=1<<2;//A portu aktif.
	RCC->APB2ENR |=1<<3;//B portu aktif.
	RCC->APB2ENR  |=1<<14;//USART1 AKTIF.
	
	
	//USART_BRR = 8,000,000 / (9,600 x 16) = 52.083.
	//(16 x 0.083) = 1.3 yaklasik 1
	//52x16+1=833 0x341
	
	GPIOA ->CRH &=0x00;//Temizleme.
	GPIOA ->CRH  =0x000004A0;// RX ve TX ayarlamalari    
	
	GPIOB ->CRL &=0x00;//Temizleme.
	GPIOB ->CRL  =0x00000022;//  B0 ve B1 led OUTPUT.
	delay_init();
	usart_init();
	
	
	while(1)
	{
		
		//Veri yollama.
		/*
		for(i=0;i<11;i++)
		{
			veri_yolla(i);
				
		delay_ms(100);
		}
		*/
		
		
		
		//Veri alma
	
		//Veri her defasinda yollanmadan once RXNE yi temizle.
		USART1 ->SR &=~(1<<5); 
		
    gelen_veri=veri_al();
		
	
		if(gelen_veri =='0')
		{
			GPIOB ->BRR =1<<0;
			GPIOB ->BSRR =1<<1;
		}
		else if(gelen_veri =='1')
		{
			GPIOB->BRR =1<<1;
			GPIOB ->BSRR =1<<0;
		}
		else if(gelen_veri =='2')
		{
			GPIOB ->BRR=1<<1;
			GPIOB ->BRR =1<<0;
		}
	  else 
		{
			GPIOB ->BSRR=1<<1;
			GPIOB ->BSRR =1<<0;
		}
		
		
	}
	
	
	
	
}




