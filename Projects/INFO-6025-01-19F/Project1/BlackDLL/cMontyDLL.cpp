#include "cMontyDLL.h"

static std::list<std::string> validColours;
static std::list<std::string> validNames;
static std::list<std::string> validQuests;
static std::string validAirSpeed;

cMontyDLL::cMontyDLL()
{
	validColours.push_back(std::string("blue"));
	validColours.push_back(std::string("red"));
	validColours.push_back(std::string("green"));

	validNames.push_back(std::string("Sir Lancelot of Camelot."));
	validNames.push_back(std::string("Robin of Camelot."));
	validNames.push_back(std::string("Sir Galahad."));
	validNames.push_back(std::string("King Arthur of the Britons!"));

	validQuests.push_back(std::string("To seek the Holy Grail."));
	validQuests.push_back(std::string("I seek the Grail!"));
	validQuests.push_back(std::string("To seek the Grail."));

	validAirSpeed = "What do you mean, an African or a European swallow?";
}



cMontyDLL::~cMontyDLL()
{

}

bool cMontyDLL::WhatIsYourFavoriteColour(const char* in)
{
	auto it = std::find(validColours.begin(), validColours.end(), in);
	return (it != validColours.end());
}

bool cMontyDLL::WhatIsYourName(const char* in)
{
	for (auto it = validNames.begin(); it != validNames.end(); ++it)
	{
	
		if (*it == in || it->find(in) != std::string::npos)
			return true;
	}
	return false;
}

bool cMontyDLL::WhatIsYourQuest(const char* in)
{
	for (auto it = validQuests.begin(); it != validQuests.end(); ++it)
	{
		if (*it == in || it->find(in) != std::string::npos)
			return true;
	}
	return false;
}

bool cMontyDLL::WhatIsTheAirSpeedOfAnUnladenSwallow(const char* in)
{
	return (in == validAirSpeed);
}