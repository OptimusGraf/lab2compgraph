#pragma once
#define _USE_MATH_DEFINES 
#include <math.h>
class FunctionTg
{
public:
	FunctionTg(const int CountOfPoint, const int CountOfPeriod);
	~FunctionTg();

	double calculateY(double x);
	void calculateArray();

	void setCountOfPoint(int count);
	void setCountOfPeriod(int count);

	int getCountOfPoint();
	int getCountOfPeriod();
	double getSizeOfPeriod();

	double* arrayOfPoint;
private:
	int CountOfPoint;
	int CountOfPeriod;

	double SizeOfPeriod;

	
};

