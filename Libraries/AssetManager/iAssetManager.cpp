#include "iAssetManager.h"

// We need this dummy operator in case classes don't override this method.
std::ostream& operator<<(std::ostream& stream, const iAssetManager& val)
{
	stream << "Got to iAssetManager by accident" << std::endl;
	return stream;
}
