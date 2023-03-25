/*
 * ADC.c
 *
 *  Created on: Jun 1, 2022
 *      Author: DELL
 */
#include "ADC.h"
#include "stm32f4xx.h"

void ADC_Init(ADCConfigType* ConfigParamPtr)
{
	RCC->APB2ENR |=(1u<<8);
	ADC1->CR2 |=(1u<<0);

	//set cont bit
    char cont = ConfigParamPtr->mode;

    if(cont){
    	ADC1->CR2 |= (1u<<1);
    }else{
    	ADC1->CR2 |= (0u<<1);
    }

	// set res
	char res = ConfigParamPtr->Resolution;
	if (res == 0)
	{
		ADC1->CR1 &=~(1u<<24); // 0 0
		ADC1->CR1 &=~(1u<<25);
	}
	else if (res == 1)
	{
		ADC1->CR1 |=(1u<<24); // 0 1
		ADC1->CR1 &=~(1u<<25);
	}
	else if (res==2)
	{
		ADC1->CR1 &=~(1u<<24); //1 0
		ADC1->CR1 |=(1u<<25);
	}
	else if (res == 3)
	{
		ADC1->CR1 &=~(1u<<24); //1 1
		ADC1->CR1 &=~(1u<<25);
	}
	else
	{
		ADC1->CR1 &=~(1u<<24); // 0 0  default
		ADC1->CR1 &=~(1u<<25);
	}



	if(USE_POLLING==1){

		ADC1->CR1 &=~(1u<<5); //disable interrupt
	}
	else{
		ADC1->CR1 |=(1u<<5);
		NVIC->ISER[0]|=(1u<<18);
	}

}

void ADC_StartConv(unsigned char ChannelNum){

	ADC1->SQR1&=~(1u<<20);
	ADC1->SQR1&=~(1u<<21);
	ADC1->SQR1&=~(1u<<22);
	ADC1->SQR1&=~(1u<<23); //one conversion

	ADC1->SQR3 &=~ ((1<<0)|(1<<1)|(1<<2)|(1<<3)|(1<<4)); // clear all bits
	ADC1->SQR3 |= (ChannelNum<<0); // write

	ADC1->CR2 |=(1u<<30);//set swstart bit

}

#if USE_POLLING
void ADC_GetConversionState(unsigned char* ConversionStatePtr)
{

	if(!(ADC1->SR & (1u<<1)))
	{
		*ConversionStatePtr = 0; /// not finished
	}else{
		*ConversionStatePtr = 1;  /// conversion done
	}

}
#endif

unsigned char ADC_ReadData(unsigned short int* DataPtr)
{
	if(ADC1->DR != 0 )
	{
	*DataPtr = ADC1->DR;
	return 0;
	}
	else
	{
	return 1;
	}
}

