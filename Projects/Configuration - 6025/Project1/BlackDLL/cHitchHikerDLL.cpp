
#include "cHitchHikerDLL.h"

cHitchHikerDLL::cHitchHikerDLL()
{

}

cHitchHikerDLL::~cHitchHikerDLL()
{

}

const char*
cHitchHikerDLL::WhatIsTheMeaningOfLife()
{
	static const char meaning[] = "42";
	return meaning;
}
