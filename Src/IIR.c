/*
 * IIR.c
 *
 *  Created on: Nov 7, 2023
 *      Author: Nguyen Ngoc Phu
 */

#include "IIR.h"

void IIR_Init(IIR *filt, float alpha){

	if (alpha < 0.0f){
		filt->alpha = 0.0f;
	} else if (alpha > 0.1f){
		filt->alpha = 0.1f;
	} else {
		filt-> alpha = alpha;
	}

	filt->out = 0.0f;
}

float IIR_Update(IIR *filt, float in){

	filt->out = (1.0f - filt->alpha) * in + filt->alpha * filt->out;

	return filt->out;
}
