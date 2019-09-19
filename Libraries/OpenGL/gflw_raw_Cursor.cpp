#include "glfw_raw_prototypes.h"
#include <gl/GlCommon.h>
#include <cassert>

namespace glfw
{
	namespace raw
	{
		void Cursor::DestroyCursor(cursor* cursor)
		{
			assert(untested);
			assert(cursor != NULL);
			glfwDestroyCursor(cursor);
		}
		cursor* Cursor::CreateCursor(const image* image, int xhot, int yhot)
		{
			assert(untested);
			assert(image != NULL);
			GLFWimage newimage = { image->width, image->height, image->pixels };
			return glfwCreateCursor(&newimage, xhot, yhot);
		}
		cursor* Cursor::CreateStandardCursor(eShape shape)
		{
			assert(untested);
			return glfwCreateStandardCursor(shape);
		}
	}
}