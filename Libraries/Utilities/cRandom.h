#pragma once

#include <cstdlib>
#include <ctime>

class cRandom
{
public:
	template <class T>
	static T randInRange(T min, T max)
	{
		double value =
			min + static_cast <double> (rand())
			/ (static_cast <double> (RAND_MAX / (static_cast<double>(max - min))));
		return static_cast<T>(value);
	};

	static void randSeed(int seed = 0)
	{
		if (seed == 0)
			srand(unsigned int(time(NULL)));
		else
			srand(seed);
	}
};


