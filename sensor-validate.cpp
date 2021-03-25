#include <math.h>
#include <stdio.h>
#include "sensor-validate.h"

#define FAILURE false
#define SUCCESS true

#define SoC_MAX_DELTA      0.05
#define Current_MAX_DELTA  0.1

/*
 * Description : Generates and returns a function which checks returns false if the absolute delta between input values is greater than max delta
 *
 */
auto generateDeltaCheckFunction(double maxDelta)
{
	return [maxDelta](double value, double nextValue){
		double delta = fabs(nextValue - value);
		return (delta > maxDelta) ? false : true ; };
}

auto Soc_SpikeCheckValidation     = generateDeltaCheckFunction(SoC_MAX_DELTA);
auto Current_SpikeCheckValidation = generateDeltaCheckFunction(Current_MAX_DELTA);

/*
 * Description : Checks if input data passes the provided validation check
 * @ Return    : False if validation Fails , True otherwise
 */
bool isReadingsValid(const double* values, int numOfValues, auto validationCheck)
{
	int lastButOneIndex = numOfValues - 1;
	for(int index = 0; index < lastButOneIndex; ++index)
	{
		if(validationCheck(values[index], values[index + 1]) == FAILURE)
		{
			return false;
		}
	}
	return true;
}


/*
 * Description : Checks if input SoC readings are valid and have no abrupt spikes in readings
 * @ Return    : Returns True if Soc Readings are valid , False otherwise
 */
bool isSOCReadingsValid(const double* values, int numOfValues)
{
	if(values != NULL && numOfValues > 0)
	{
		return isReadingsValid(values, numOfValues, Soc_SpikeCheckValidation);
	}
	return false;
}

/*
 * Description : Checks if input Current readings are valid and have no abrupt spikes in readings
 * @ Return    : Returns True if Current Readings are valid , False otherwise
 */
bool isCurrentReadingsValid(const double* values, int numOfValues)
{
	if(values != NULL && numOfValues > 0)
	{
		return isReadingsValid(values, numOfValues, Current_SpikeCheckValidation);
	}
	return false;
}
