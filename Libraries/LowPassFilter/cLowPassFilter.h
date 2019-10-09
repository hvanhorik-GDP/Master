#pragma once

#include <vector>

#pragma comment(lib, "LowPassFilter.lib")

class cLowPassFilter
{
public:
	cLowPassFilter();
	void addValue(double newValue);
	double getAverage(void);

private:
	std::vector<double> vecTimes;
	std::vector<double>::size_type m_NextLocation;

	// Pick a value that's about the number of frames...
	static const int DEFAULTVECTORSIZE = 50;

};