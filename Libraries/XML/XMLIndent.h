#pragma once

#include <ostream>

class XMLIndent
{
public:
	XMLIndent(int level) : level(level) {}
	friend std::ostream& operator<<(std::ostream& stream, const XMLIndent& val);
	int level;
};
