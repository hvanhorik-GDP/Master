// Raw methods for gflw System methods

#include <gl/GLCommon.h>		// glfw.h, etc. (openGL.h)
#include "glfw_raw_prototypes.h"
#include <cassert>

namespace glfw
{
	namespace raw
	{
		const char* System::GetVersionString(void)
		{
			assert(untested);
			return glfwGetVersionString();
		}

		const char** System::GetRequiredInstanceExtensions(uint32_t* count)
		{
			assert(count != NULL);
			assert(untested);
			return glfwGetRequiredInstanceExtensions(count);
		}

		double System::GetTime(void)
		{	
			assert(untested);
			return glfwGetTime();
		}

		glproc System::GetProcAddress(const char* procname)
		{
			assert(procname != NULL);
			assert(untested);
			return glfwGetProcAddress(procname);
		}

		int System::ExtensionSupported(const char* extension)
		{
			assert(extension != NULL);
			assert(untested);
			return glfwExtensionSupported(extension);
		}
		int System::Init(void)
		{
			assert(untested);
			return glfwInit();
		}

		int System::VulkanSupported(void)
		{
			assert(untested);
			return glfwVulkanSupported();
		}

		uint64_t System::GetTimerFrequency(void)
		{
			assert(untested);
			return glfwGetTimerFrequency();
		}

		uint64_t System::GetTimerValue(void)
		{
			assert(untested);
			return glfwGetTimerValue();
		}

		//				vkproc System::GetInstanceProcAddress(VkInstance instance, const char* procname);

		void System::GetVersion(int* major, int* minor, int* rev)
		{
			assert(untested);
			assert(major != NULL);
			assert(minor != NULL);
			assert(rev != NULL);
			return glfwGetVersion(major, minor, rev);
		}

		void System::PollEvents(void)
		{
			assert(untested);
			glfwPollEvents();
		}

		void System::PostEmptyEvent(void)
		{
			assert(untested);
			glfwPostEmptyEvent();
		}

		void System::SetTime(double time)
		{
			assert(untested);
			glfwSetTime(time);
		}

		void System::SwapInterval(int interval)
		{
			assert(untested);
			glfwSwapInterval(interval);
		}

		void System::Terminate(void)
		{
			assert(untested);
			glfwTerminate();
		}
		void System::WaitEvents(void)
		{
			assert(untested);
			glfwWaitEvents();
		}

		void System::WaitEventsTimeout(double timeout)
		{
			assert(untested);
			glfwWaitEventsTimeout(timeout);
		}
	}
}