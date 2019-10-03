// A way to pass items around
#include <ostream>

class iItem
{
public:
	iItem() {};
	virtual ~iItem() {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iItem& val);
};
