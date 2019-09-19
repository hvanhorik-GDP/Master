
#include "glfw_raw_prototypes.h"
#include <gl/GlCommon.h>
#include <cassert>

namespace glfw
{
	namespace raw
	{
		const char* Key::GetKeyName(Key::eKey key, int scancode)
		{
			union
			{
				int iKey;
				eKey enumKey;
			} parms;

			assert(untested);
			const char* ret = glfwGetKeyName(key, scancode);
			assert(ret != NULL);
			return ret;
		}
	}
}