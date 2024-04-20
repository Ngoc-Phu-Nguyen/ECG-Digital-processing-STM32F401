#ifndef NOTCH_FILTER_H
#define NOTCH_FILTER_H

#include "math.h"

typedef struct{
	float sampleFreq_Hz; // depend on the ADC rate! 

	float alpha;
	float beta;

	float x[3];

	float y[3];
} NotchFilter;

void NotchFilter_Init(NotchFilter *filt, float centerFreq_Hz, float notchWidth_Hz, float sampleFreq_Hz);
void NotchFilter_SetCenterFreqHz(NotchFilter *filt, float centerFreq_Hz);
void NotchFilter_NotchWidtghHz(NotchFilter *filt, float notchWidth_Hz);
float NotchFilter_Update(NotchFilter *filt, float in);

#endif
