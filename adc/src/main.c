#include "stm32f4xx.h"
#include "gpio.h"
#include "ADC.h"
#include "LCD.h"

unsigned short int Data;
unsigned short int* DataPtr=&Data;
unsigned short int Temperature;
unsigned char ConversionState;
unsigned char* ConversionStatePointer=&ConversionState;


int main(void)
{

	LCD_Init();
//	for(int i = 0; i<8; i++)
//		 {
//	GPIO_Init (GPIOB,i,1,0);
//		 }
//        initialization
// Enable clock to GPIOA
	RCC->AHB1ENR |=(1u<<0);

	// pin 0 to analog mmode
	GPIOA->MODER |= (1u<<0);
	GPIOA->MODER |= (1u<<1);

	ADCConfigType configuration = {twelveB,ContinousMood,1.5};
	ADCConfigType* ConfigParamPtr = & configuration;
	ADC_Init(ConfigParamPtr);

	double ref_voltage = ConfigParamPtr->Vref;

	ADC_StartConv(0);



	while(1)
	{



		ADC_GetConversionState(ConversionStatePointer);
		if(ConversionState){

			ADC_ReadData(DataPtr);

			LCD_ClearScreen();
			Temperature =(int)((Data/(1.5f * 4095.0f)) * ref_voltage * 150.0f);
			LCD_DisplayString("Current temp: ");
			LCD_MoveCursor(1,0);
			LCD_IntToStr(Temperature);
			LCD_DisplayString(" C");
			for(int j =0 ; j<500000;j++){}// delay for some time

		}




		// for interrupt check EOCIE bit
	}
}

void ADC_IRQHandler(void){

	ADC_ReadData(DataPtr);

}
