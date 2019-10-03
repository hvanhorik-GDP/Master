#include <ostream>
// A way to pass items around
class iItem
{
public:
	iItem() {};
	virtual ~iItem() {}

	// For debugging purposes - dumps the contents in human readable form
	friend std::ostream& operator<<(std::ostream& stream, const iItem& val);
};
