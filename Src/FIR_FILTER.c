#include <FIR_FILTER.h>

static float FIR_IMPULSE_RESPONSE_AV[FIR_FILTER_LENGTH_AV] = {
	0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f,0.05f
};
static double FIR_IMPULSE_RESPONSE_LP[FIR_FILTER_LENGTH] ={
		-0.008693024696459424,
		-0.00939685875531001,
		-0.010302057657848963,
		-0.006370619029881777,
		0.004259289492238358,
		0.02287385178043612,
		0.048662779461861164,
		0.07941296074243773,
		0.11087128869862442,
		0.13837440536890327,
		0.15703461855115433,
		0.1637360361264547,
		0.15703461855115433,
		0.13837440536890327,
		0.11087128869862442,
		0.07941296074243773,
		0.048662779461861164,
		0.02287385178043612,
		0.004259289492238358,
		-0.006370619029881777,
		-0.010302057657848963,
		-0.00939685875531001,
		-0.008693024696459424
};// Low pass filter with 0 - 100 Hz  http://t-filter.engineerjs.com/

void FIRFilter_Init(FIRFilter *fir)
{
	/*clear filter buffer*/
	for (uint8_t n=0; n<FIR_FILTER_LENGTH; n++)
	{
		fir->buf[n] = 0.0f;
	}
	/*Reset buffer index*/
	fir->bufIndex = 0;

	/*Clear filter output*/
	fir->out = 0.0f;
}
void FIRFilter_AV_Init(FIRFilter_AV *fir)
{
	/*clear filter buffer*/
	for (uint8_t n=0; n<FIR_FILTER_LENGTH_AV; n++)
	{
		fir->buf[n] = 0.0f;
	}
	/*Reset buffer index*/
	fir->bufIndex = 0;

	/*Clear filter output*/
	fir->out = 0.0f;
}

float FIRFilter_Update(FIRFilter *fir, float inp)
{
	/*Store latest sample in buffer*/
	fir->buf[fir->bufIndex] = inp;
	/*Increment buffer index and wrap around if necessary*/
	fir->bufIndex++;
	if (fir->bufIndex == FIR_FILTER_LENGTH)
	{
		fir -> bufIndex = 0;
	}
	/* Compute(reset) new output sample  (via convolution) */
	fir -> out = 0.0f;
	uint8_t streamIndex = fir->bufIndex;

	for (uint8_t n = 0; n< FIR_FILTER_LENGTH; n++)
	{
		/*Decrement index and wrap if necessary*/
		if (streamIndex >0){
		streamIndex--;
		}else 
		{
			streamIndex = FIR_FILTER_LENGTH -1;
		}
	/* Multiply impulse response with shifted input sample and add to output*/
		fir -> out += FIR_IMPULSE_RESPONSE_LP[n] * fir->buf[streamIndex];
	/*Return filtered output*/

	} 
	
	return fir -> out;
}

float FIRFilter_AV_Update(FIRFilter_AV *fir, float inp)
{
	/*Store latest sample in buffer*/
	fir->buf[fir->bufIndex] = inp;
	/*Increment buffer index and wrap around if necessary*/
	fir->bufIndex++;
	if (fir->bufIndex == FIR_FILTER_LENGTH_AV)
	{
		fir -> bufIndex = 0;
	}
	/* Compute(reset) new output sample  (via convolution) */
	fir -> out = 0.0f;
	uint8_t streamIndex = fir->bufIndex;

	for (uint8_t n = 0; n< FIR_FILTER_LENGTH_AV; n++)
	{
		/*Decrement index and wrap if necessary*/
		if (streamIndex >0){
		streamIndex--;
		}else 
		{
			streamIndex = FIR_FILTER_LENGTH_AV -1;
		}
	/* Multiply impulse response with shifted input sample and add to output*/
		fir -> out += FIR_IMPULSE_RESPONSE_AV[n] * fir->buf[streamIndex];
	/*Return filtered output*/

	} 
	
	return fir -> out;
}
