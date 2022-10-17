#include "FunctionTg.h"

FunctionTg::FunctionTg(int CountOfPoint, const int CountOfPeriod)
{
	if (CountOfPoint % 2 != 0)
		CountOfPoint++;
	this->CountOfPoint = CountOfPoint;
	this->CountOfPeriod = CountOfPeriod;
	this->SizeOfPeriod = M_PI;

	arrayOfPoint = new double[CountOfPoint * 2];

	calculateArray();

}

FunctionTg::~FunctionTg()
{
	delete[] arrayOfPoint;
}

double FunctionTg::calculateY(double x)
{
	return tan(x);
}

void FunctionTg::calculateArray()
{

	for (int i = 0; i < CountOfPoint * 2; i += 2)
	{
		double x = SizeOfPeriod / CountOfPoint * i / 2 - SizeOfPeriod / 2;
		arrayOfPoint[i] = x;
		arrayOfPoint[i + 1] = calculateY(x);
	}
}

void FunctionTg::setCountOfPoint(int count)
{
	CountOfPoint = count;
	void calculateArray();
}

void FunctionTg::setCountOfPeriod(int count)
{
	CountOfPeriod = count;
}

int FunctionTg::getCountOfPoint()
{
	return CountOfPoint;
}

int FunctionTg::getCountOfPeriod()
{
	return CountOfPeriod;
}

double FunctionTg::getSizeOfPeriod()
{
	return SizeOfPeriod;
}

double* FunctionTg::GetArrayOfPoint()
{
	return arrayOfPoint;
}
