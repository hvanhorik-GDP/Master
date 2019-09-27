// WhiteTest.cpp
//

#include <iostream>
#include <gtest/gtest.h>

#include "cMonty.h"
#include "cHitchHiker.h"

using namespace std;

cHitchHiker hiker;
cMonty monty;

//“The best things in life make you sweaty.”
//“Life is problems.Living is solving problems.”
//"To be happy we need something to solve. Happiness is therefore a form of action;"
//“The Ultimate Answer to Life, The Universeand Everything is...42!”

TEST(WhatIsTheMeaningOfLife, Sweaty)
{
	EXPECT_STRNE(hiker.WhatIsTheMeaningOfLife(), "The best things in life make you sweaty.");
}

TEST(WhatIsTheMeaningOfLife, SolvingProblems)
{
	EXPECT_STRNE(hiker.WhatIsTheMeaningOfLife(), "Life is problems. Living is solving problems.");
}

TEST(WhatIsTheMeaningOfLife, FormOfAction)
{
	EXPECT_STRNE(hiker.WhatIsTheMeaningOfLife(), "To be happy we need something to solve. Happiness is therefore a form of action;");
}

// I couldn't figure out how to test for a string within a string so I wrote a helper function
namespace HelperFunctions
{
	bool isIn(const char* in, const char* answer)
	{
		return (std::strstr(hiker.WhatIsTheMeaningOfLife(), "42") != 0);
	}
}

TEST(WhatIsTheMeaningOfLife, UltimateAnswer)
{
	EXPECT_EQ(HelperFunctions::isIn("The Ultimate Answer to Life, The Universeand Everything is...42!", hiker.WhatIsTheMeaningOfLife()), true );
}

TEST(WhatIsTheMeaningOfLife, 42)
{
	EXPECT_STREQ(hiker.WhatIsTheMeaningOfLife(), "42");
}

TEST(WhatIsYourFavoriteColour, blue)
{
	EXPECT_EQ(monty.WhatIsYourFavoriteColour("blue"), true);
}

TEST(WhatIsYourFavoriteColour, red)
{
	EXPECT_EQ(monty.WhatIsYourFavoriteColour("red"), true);
}

TEST(WhatIsYourFavoriteColour, green)
{
	EXPECT_EQ(monty.WhatIsYourFavoriteColour("green"), true);
}

TEST(WhatIsYourFavoriteColour, IDontKnow)
{
	EXPECT_EQ(monty.WhatIsYourFavoriteColour("I Don't Know"), false);
}

TEST(WhatIsYourFavoriteColour, RedNoGreen)
{
	EXPECT_EQ(monty.WhatIsYourFavoriteColour("Blue. No..."), false);
}

TEST(WhatIsYourName, Galahad)
{
	EXPECT_EQ(monty.WhatIsYourName("Galahad"), true);
	// Sir Galahad.
}

TEST(WhatIsYourName, SirGalahad)
{
	EXPECT_EQ(monty.WhatIsYourName("Sir Galahad."), true);
}

TEST(WhatIsYourName, KingArthur)
{
	EXPECT_EQ(monty.WhatIsYourName("King Arthur of the Britons!"), true);
}

TEST(WhatIsYourName, SirLancelot)
{
	EXPECT_EQ(monty.WhatIsYourName("Sir Lancelot"), true);
}

TEST(WhatIsYourName, LukasGustafson)
{
	EXPECT_EQ(monty.WhatIsYourName("Lukas Gustafson"), false);
}

TEST(WhatIsYourQuest, Grail)
{
	EXPECT_EQ(monty.WhatIsYourQuest("Grail"), true);
}

TEST(WhatIsYourQuest, HolyGrail)
{
	EXPECT_EQ(monty.WhatIsYourQuest("Holy Grail"), true);
}

TEST(WhatIsYourQuest, ToSeekHolyGrail)
{
	EXPECT_EQ(monty.WhatIsYourQuest("To seek the Holy Grail."), true);
}

TEST(WhatIsYourQuest, ISeekHolyGrail)
{
	EXPECT_EQ(monty.WhatIsYourQuest("I seek the Grail!"), true);
}

TEST(WhatIsYourQuest, ToPassThisProject)
{
	EXPECT_EQ(monty.WhatIsYourQuest("To Pass This Project"), false);
}

TEST(WhatIsTheAirSpeedOfAnUnladenSwallow, IDontKnow)
{
	EXPECT_EQ(monty.WhatIsTheAirSpeedOfAnUnladenSwallow("I don't know"), false);
}

TEST(WhatIsTheAirSpeedOfAnUnladenSwallow, 32)
{
	EXPECT_EQ(monty.WhatIsTheAirSpeedOfAnUnladenSwallow("32"), false);
}

TEST(WhatIsTheAirSpeedOfAnUnladenSwallow, 28Mph)
{
	EXPECT_EQ(monty.WhatIsTheAirSpeedOfAnUnladenSwallow("28Mph"), false);
}
TEST(WhatIsTheAirSpeedOfAnUnladenSwallow, 40KPH)
{
	EXPECT_EQ(monty.WhatIsTheAirSpeedOfAnUnladenSwallow("40KPH"), false);
}
TEST(WhatIsTheAirSpeedOfAnUnladenSwallow, AfricanOrEuropean)
{
	EXPECT_EQ(monty.WhatIsTheAirSpeedOfAnUnladenSwallow("What do you mean, an African or a European swallow?"), true);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);

	int i = std::strcmp(hiker.WhatIsTheMeaningOfLife(), "42");

	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

