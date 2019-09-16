#pragma once

#include <string>

#define DLLExport __declspec(dllexport)

class DLLExport cHitchHikerDLL
{
public:
	cHitchHikerDLL();
	~cHitchHikerDLL();

	const char* WhatIsTheMeaningOfLife();
};