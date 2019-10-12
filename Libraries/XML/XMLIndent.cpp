#include "XMLIndent.h"

std::ostream& operator<<(std::ostream& stream, const XMLIndent& val)
{
	for (int i = 0; i < val.level; i++) {
		stream << " ";
	}
	return stream;
}
