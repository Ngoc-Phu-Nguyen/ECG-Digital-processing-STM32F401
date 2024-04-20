/*
 * NotchFilter.c
 *
 *  Created on: Nov 1, 2023
 *      Author: Nguyen Ngoc Phu
 */
#include "NotchFilter.h"

void NotchFilter_Init(NotchFilter *filt, float centerFreq_Hz, float notchWidth_Hz, float sampleFreq_Hz){

	filt->sampleFreq_Hz = sampleFreq_Hz;

	NotchFilter_SetCenterFreqHz(filt, centerFreq_Hz);
	NotchFilter_NotchWidtghHz(filt, notchWidth_Hz);




	for (unsigned char  n = 0; n<3; n++){
		filt->x[n] = 0.0f;
		filt->y[n] = 0.0f;
	}
}

void NotchFilter_SetCenterFreqHz(NotchFilter *filt, float centerFreq_Hz){

	float w0_rps = 2.0f * M_PI * centerFreq_Hz;
	float w0_pw_rps = (2.0 * filt->sampleFreq_Hz ) * tanf(0.5f * w0_rps / filt->sampleFreq_Hz);
	filt->alpha = 4.0f + w0_pw_rps * w0_pw_rps / (filt->sampleFreq_Hz * filt->sampleFreq_Hz);
}
void NotchFilter_NotchWidtghHz(NotchFilter *filt, float notchWidth_Hz){

	float ww_rps = 2.0f * M_PI * notchWidth_Hz;
	filt->beta = 2.0f * ww_rps /  filt->sampleFreq_Hz;
}

float NotchFilter_Update(NotchFilter * filt, float in){
	filt->x[2] = filt->x[1];
	filt->x[1] = filt->x[0];

	filt->y[2] = filt->y[1];
	filt->y[1] = filt->y[0];

	filt->x[0] = in;

	filt->y[0] = (filt->alpha * filt->x[0] + 2.0f * (filt->alpha - 8.0f) * filt->x[1] + filt->alpha * filt->x[2]
				- 2.0f * (filt->alpha - 8.0f) * filt->y[1] - (filt->alpha - filt->beta) * filt->y[2])
				/ (filt->alpha + filt->beta);
	//filt->y[0] = (0.9995f * filt->x[0] - 1.996f * filt->x[1] + 0.999f * filt->x[2] + 1.996 * filt->y[1] - 0.9987 * filt->y[2]);

	return filt->y[0];

}
