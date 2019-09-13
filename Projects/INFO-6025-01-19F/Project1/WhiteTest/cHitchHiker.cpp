
#include "cHitchHiker.h"

cHitchHiker::cHitchHiker()
{

}

cHitchHiker::~cHitchHiker()
{

}

const char*
cHitchHiker::WhatIsTheMeaningOfLife()
{
	static const char meaning[] = "42";
	return meaning;
}
