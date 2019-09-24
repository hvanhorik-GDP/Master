#include "engine_System.h"

#include "boost/serialization/singleton.hpp"

namespace engine
{
	class SystemImpl
	{
	};

	boost::serialization::singleton<SystemImpl> gSystemImpl;
}

class System : 