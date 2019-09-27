#pragma once

#include <string>
#include <list>

#define DLLExport __declspec(dllexport)

class DLLExport cMontyDLL
{
public:
	cMontyDLL();
	~cMontyDLL();

	bool WhatIsYourFavoriteColour(const char* in);
	bool WhatIsYourName(const char* in);
	bool WhatIsYourQuest(const char* in);
	bool WhatIsTheAirSpeedOfAnUnladenSwallow(const char* in);
};

