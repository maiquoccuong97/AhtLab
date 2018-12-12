#include "delay.h"

#define PortLed			GPIOA
#define PortButton		GPIOE
#define Led1			GPIO_Pin_1	
#define Led2			GPIO_Pin_5	
#define UserButton		GPIO_Pin_2	
#define UserButton1		GPIO_Pin_3	

/* Declare Variable */
uint8_t tt=0;

/*Declare Struct*/
GPIO_InitTypeDef GPIO_InitStructure;

/*Declare Function*/
void Init_GPIO(void);


/*------------Interrupt Systick-------------*/
void SysTick_Handler()
{
	TimingDelay_Decrement();
}


void Init_GPIO()
{
	/*setting PORT Led*/
	/* enable GPIOA */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 

  GPIO_InitStructure.GPIO_Pin = Led1 | Led2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // Push Pull.
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(PortLed, &GPIO_InitStructure);
	
	/*setting PORT User Button*/
	/* enable GPIOE */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  GPIO_InitStructure.GPIO_Pin = UserButton | UserButton1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(PortButton, &GPIO_InitStructure);
}


int main()
{
	
	/*---------Initialise Clock---------*/
	SystemCoreClockUpdate();       /* Get Core Clock Frequency: // 1/168MHz=5.952ns. */
    if (SysTick_Config(SystemCoreClock / 1000))  // 16MHz/1000.
    { /* SysTick-System_Timer 1 msec interrupts  */
              while (1);         /* Capture error */
    }
	
	Init_GPIO();																	
	while(1)
	{
		/* //Chop tat Led1.
		GPIO_SetBits(PortLed,Led1);
		delay_ms(300);
	    GPIO_ResetBits(PortLed,Led1);
		delay_ms(300);   */
		
        /* //Nut nhan RE2 khong chong doi.		
        if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)==1)
		{
				GPIO_SetBits(PortLed,Led1);
				GPIO_SetBits(PortLed,Led2);
		}
		else
	    {
				GPIO_ResetBits(PortLed,Led1);
				GPIO_ResetBits(PortLed,Led2);
		}  */
		
		if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))
		{
			delay_ms(200);
			if(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2))
			{
				tt=~tt;
				if(tt)  GPIO_SetBits(PortLed,Led1|Led2);
				else    GPIO_ResetBits(PortLed,Led1|Led2);
				while(!GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2));
			}
		}
		
	}
}
