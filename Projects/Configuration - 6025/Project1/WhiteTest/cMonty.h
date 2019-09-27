#pragma once

#include <string>
#include <list>

class cMonty
{
public:
	cMonty();
	~cMonty();

	bool WhatIsYourFavoriteColour(const char* in);
	bool WhatIsYourName(const char* in);
	bool WhatIsYourQuest(const char* in);
	bool WhatIsTheAirSpeedOfAnUnladenSwallow(const char* in);
private:
	std::list<std::string> validColours;
	std::list<std::string> validNames;
	std::list<std::string> validQuests;
	std::string validAirSpeed;
};

