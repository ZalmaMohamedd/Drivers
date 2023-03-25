/*
 * ADC.h
 *
 *  Created on: Jun 1, 2022
 *      Author: DELL
 */

#ifndef INCLUDE_ADC_H_
#define INCLUDE_ADC_H_

#define USE_POLLING 1
typedef enum {twelveB ,tenB,eightB,sixB}Resolution ;
typedef enum {SingleMood,ContinousMood}Mode ;

typedef struct ADCConfigType{
	Resolution  Resolution;
	Mode mode;
    double Vref;
}ADCConfigType;




void ADC_Init(ADCConfigType* ConfigParamPtr);
void ADC_StartConv(unsigned char ChannelNum);
void ADC_GetConversionState(unsigned char* ConversionStatePtr);
unsigned char ADC_ReadData(unsigned short int* DataPtr);

#endif /* INCLUDE_ADC_H_ */
