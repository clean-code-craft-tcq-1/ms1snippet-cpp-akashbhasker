#include <math.h>
#include "sensor-validate.h"

#define FAILURE false
#define SUCCESS true

#define SoC_MAX_DELTA      0.05
#define Current_MAX_DELTA  0.1

/*
 *
 */
auto generateDeltaCheckFunction(double maxDelta)
{
	return [maxDelta](double value, double nextValue){
		double delta = fabs(nextValue - value);
		return (delta > maxDelta) ? false : true ; };
}

auto Soc_SpikeCheck     = generateDeltaCheckFunction(SoC_MAX_DELTA);
auto Current_SpikeCheck = generateDeltaCheckFunction(Current_MAX_DELTA);

/*
 *
 */
bool isSpikeInReadingsObserved(const double* values, int numOfValues,auto spikeCheckValidation)
{
	int lastButOneIndex = numOfValues - 1;
	for(int index = 0; index < lastButOneIndex; ++index)
	{
		if(spikeCheckValidation(values[index], values[index + 1]) == FAILURE)
		{
			return false;
		}
	}
	return true;
}

/*
 *
 */
bool validateSOCreadings(const double* values, int numOfValues)
{
	if(numOfValues > 0)
	{
		return isSpikeInReadingsObserved(values, numOfValues, Soc_SpikeCheck);
	}
	return false;
}

/*
 *
 */
bool validateCurrentreadings(const double* values, int numOfValues)
{
	if(numOfValues > 0)
	{
		return isSpikeInReadingsObserved(values, numOfValues, Current_SpikeCheck);
	}
	return false;
}
