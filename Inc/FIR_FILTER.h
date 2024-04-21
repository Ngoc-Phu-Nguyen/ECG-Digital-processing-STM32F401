#ifndef FIR_FILTER_H
#define FIR_FILTER_H

#include <stdint.h>

#define FIR_FILTER_LENGTH 23
#define FIR_FILTER_LENGTH_AV 20

typedef struct {
	double buf[FIR_FILTER_LENGTH];
	uint8_t bufIndex;
	double out;
} FIRFilter;

typedef struct {
	float buf[FIR_FILTER_LENGTH_AV];
	uint8_t bufIndex;
	float out;
} FIRFilter_AV;

void FIRFilter_Init(FIRFilter *fir);
void FIRFilter_AV_Init(FIRFilter_AV *fir);
float FIRFilter_Update(FIRFilter *fir, float inp);
float FIRFilter_AV_Update(FIRFilter_AV *fir, float inp);


#endif
