#include "iObjectManagerPart.h"


// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const iObjectManagerPart& val)
{
	stream << "Got to iObjectManagerPart by accident" << std::endl;
	return stream;
}
