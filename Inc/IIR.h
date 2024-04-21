/*
 * IIR.h
 *
 *  Created on: Nov 7, 2023
 *      Author: Nguyen Ngoc Phu
 */

#ifndef INC_IIR_H_
#define INC_IIR_H_

typedef struct{
	float alpha;
	float out;
} IIR;

void IIR_Init (IIR * filt, float alpha);

float IIR_Update(IIR *filt, float in);

#endif /* INC_IIR_H_ */
