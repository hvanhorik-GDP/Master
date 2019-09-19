#pragma once

#include <cinttypes>

// This is an attempt to put all of the openGL functions in a logical order 
// These will just be flowthrough methods so I can get rid of all OpenGL from my other code
// Note the deep namespace to make it irritating for anyone to actually use these apis.
//

typedef struct GLFWcursor GLFWcursor;
typedef struct GLFWmonitor GFWmonitor;
typedef struct GLFWwindow GLFWwindow;

namespace glfw
{
	namespace raw
	{
		bool untested = false;

		typedef void (*glproc)(void);
		typedef void (*vkproc)(void);
		typedef struct GLFWmonitor monitor;
		typedef struct GLFWwindow window;
		typedef struct GLFWcursor cursor;
		typedef struct image
		{
			int width;
			int height;
			unsigned char* pixels;
		} image;

		enum eOther
		{
			VersionMajor = 3,				// GLFW_VERSION_MAJOR
			VersionMinor = 2,				// GLFW_VERSION_MINOR
			VersionRevision = 1,				// GLFW_VERSION_REVISION
			True = 1,				// GLFW_TRUE
			False = 0,				// GLFW_FALSE
			Release = 0,				// GLFW_RELEASE
			Press = 1,				// GLFW_PRESS
			Repeat = 2,				// GLFW_REPEAT
			Connected = 0x00040001,				// GLFW_CONNECTED
			Disconnected = 0x00040002,				// GLFW_DISCONNECTED
			DontCare = -1,				// GLFW_DONT_CARE
		} eOther;	// eOther

		namespace Key
		{
			enum eKey
			{
				KeyUnknown = -1,				// GLFW_KEY_UNKNOWN
				KeySpace = 32,				// GLFW_KEY_SPACE
				KeyApostrophe = 39,				// GLFW_KEY_APOSTROPHE
				KeyComma = 44,				// GLFW_KEY_COMMA
				KeyMinus = 45,				// GLFW_KEY_MINUS
				KeyPeriod = 46,				// GLFW_KEY_PERIOD
				KeySlash = 47,				// GLFW_KEY_SLASH
				Key_0 = 48,				// GLFW_KEY_0
				Key_1 = 49,				// GLFW_KEY_1
				Key_2 = 50,				// GLFW_KEY_2
				Key_3 = 51,				// GLFW_KEY_3
				Key_4 = 52,				// GLFW_KEY_4
				Key_5 = 53,				// GLFW_KEY_5
				Key_6 = 54,				// GLFW_KEY_6
				Key_7 = 55,				// GLFW_KEY_7
				Key_8 = 56,				// GLFW_KEY_8
				Key_9 = 57,				// GLFW_KEY_9
				KeySemicolon = 59,				// GLFW_KEY_SEMICOLON
				KeyEqual = 61,				// GLFW_KEY_EQUAL
				KeyA = 65,				// GLFW_KEY_A
				KeyB = 66,				// GLFW_KEY_B
				KeyC = 67,				// GLFW_KEY_C
				KeyD = 68,				// GLFW_KEY_D
				KeyE = 69,				// GLFW_KEY_E
				KeyF = 70,				// GLFW_KEY_F
				KeyG = 71,				// GLFW_KEY_G
				KeyH = 72,				// GLFW_KEY_H
				KeyI = 73,				// GLFW_KEY_I
				KeyJ = 74,				// GLFW_KEY_J
				KeyK = 75,				// GLFW_KEY_K
				KeyL = 76,				// GLFW_KEY_L
				KeyM = 77,				// GLFW_KEY_M
				KeyN = 78,				// GLFW_KEY_N
				KeyO = 79,				// GLFW_KEY_O
				KeyP = 80,				// GLFW_KEY_P
				KeyQ = 81,				// GLFW_KEY_Q
				KeyR = 82,				// GLFW_KEY_R
				KeyS = 83,				// GLFW_KEY_S
				KeyT = 84,				// GLFW_KEY_T
				KeyU = 85,				// GLFW_KEY_U
				KeyV = 86,				// GLFW_KEY_V
				KeyW = 87,				// GLFW_KEY_W
				KeyX = 88,				// GLFW_KEY_X
				KeyY = 89,				// GLFW_KEY_Y
				KeyZ = 90,				// GLFW_KEY_Z
				KeyLeftBracket = 91,				// GLFW_KEY_LEFT_BRACKET
				KeyBackslash = 92,				// GLFW_KEY_BACKSLASH
				KeyRightBracket = 93,				// GLFW_KEY_RIGHT_BRACKET
				KeyGraveAccent = 96,				// GLFW_KEY_GRAVE_ACCENT
				KeyWorld_1 = 161,				// GLFW_KEY_WORLD_1
				KeyWorld_2 = 162,				// GLFW_KEY_WORLD_2
				KeyEscape = 256,				// GLFW_KEY_ESCAPE
				KeyEnter = 257,				// GLFW_KEY_ENTER
				KeyTab = 258,				// GLFW_KEY_TAB
				KeyBackspace = 259,				// GLFW_KEY_BACKSPACE
				KeyInsert = 260,				// GLFW_KEY_INSERT
				KeyDelete = 261,				// GLFW_KEY_DELETE
				KeyRight = 262,				// GLFW_KEY_RIGHT
				KeyLeft = 263,				// GLFW_KEY_LEFT
				KeyDown = 264,				// GLFW_KEY_DOWN
				KeyUp = 265,				// GLFW_KEY_UP
				KeyPageUp = 266,				// GLFW_KEY_PAGE_UP
				KeyPageDown = 267,				// GLFW_KEY_PAGE_DOWN
				KeyHome = 268,				// GLFW_KEY_HOME
				KeyEnd = 269,				// GLFW_KEY_END
				KeyCapsLock = 280,				// GLFW_KEY_CAPS_LOCK
				KeyScrollLock = 281,				// GLFW_KEY_SCROLL_LOCK
				KeyNumLock = 282,				// GLFW_KEY_NUM_LOCK
				KeyPrintScreen = 283,				// GLFW_KEY_PRINT_SCREEN
				KeyPause = 284,				// GLFW_KEY_PAUSE
				KeyF1 = 290,				// GLFW_KEY_F1
				KeyF2 = 291,				// GLFW_KEY_F2
				KeyF3 = 292,				// GLFW_KEY_F3
				KeyF4 = 293,				// GLFW_KEY_F4
				KeyF5 = 294,				// GLFW_KEY_F5
				KeyF6 = 295,				// GLFW_KEY_F6
				KeyF7 = 296,				// GLFW_KEY_F7
				KeyF8 = 297,				// GLFW_KEY_F8
				KeyF9 = 298,				// GLFW_KEY_F9
				KeyF10 = 299,				// GLFW_KEY_F10
				KeyF11 = 300,				// GLFW_KEY_F11
				KeyF12 = 301,				// GLFW_KEY_F12
				KeyF13 = 302,				// GLFW_KEY_F13
				KeyF14 = 303,				// GLFW_KEY_F14
				KeyF15 = 304,				// GLFW_KEY_F15
				KeyF16 = 305,				// GLFW_KEY_F16
				KeyF17 = 306,				// GLFW_KEY_F17
				KeyF18 = 307,				// GLFW_KEY_F18
				KeyF19 = 308,				// GLFW_KEY_F19
				KeyF20 = 309,				// GLFW_KEY_F20
				KeyF21 = 310,				// GLFW_KEY_F21
				KeyF22 = 311,				// GLFW_KEY_F22
				KeyF23 = 312,				// GLFW_KEY_F23
				KeyF24 = 313,				// GLFW_KEY_F24
				KeyF25 = 314,				// GLFW_KEY_F25
				KeyKp_0 = 320,				// GLFW_KEY_KP_0
				KeyKp_1 = 321,				// GLFW_KEY_KP_1
				KeyKp_2 = 322,				// GLFW_KEY_KP_2
				KeyKp_3 = 323,				// GLFW_KEY_KP_3
				KeyKp_4 = 324,				// GLFW_KEY_KP_4
				KeyKp_5 = 325,				// GLFW_KEY_KP_5
				KeyKp_6 = 326,				// GLFW_KEY_KP_6
				KeyKp_7 = 327,				// GLFW_KEY_KP_7
				KeyKp_8 = 328,				// GLFW_KEY_KP_8
				KeyKp_9 = 329,				// GLFW_KEY_KP_9
				KeyKpDecimal = 330,				// GLFW_KEY_KP_DECIMAL
				KeyKpDivide = 331,				// GLFW_KEY_KP_DIVIDE
				KeyKpMultiply = 332,				// GLFW_KEY_KP_MULTIPLY
				KeyKpSubtract = 333,				// GLFW_KEY_KP_SUBTRACT
				KeyKpAdd = 334,				// GLFW_KEY_KP_ADD
				KeyKpEnter = 335,				// GLFW_KEY_KP_ENTER
				KeyKpEqual = 336,				// GLFW_KEY_KP_EQUAL
				KeyLeftShift = 340,				// GLFW_KEY_LEFT_SHIFT
				KeyLeftControl = 341,				// GLFW_KEY_LEFT_CONTROL
				KeyLeftAlt = 342,				// GLFW_KEY_LEFT_ALT
				KeyLeftSuper = 343,				// GLFW_KEY_LEFT_SUPER
				KeyRightShift = 344,				// GLFW_KEY_RIGHT_SHIFT
				KeyRightControl = 345,				// GLFW_KEY_RIGHT_CONTROL
				KeyRightAlt = 346,				// GLFW_KEY_RIGHT_ALT
				KeyRightSuper = 347,				// GLFW_KEY_RIGHT_SUPER
				KeyMenu = 348,				// GLFW_KEY_MENU
				KeyLast = KeyMenu,				// GLFW_KEY_LAST
			};
			enum eModifier
			{
				ModShift = 0x0001,				// GLFW_MOD_SHIFT
				ModControl = 0x0002,				// GLFW_MOD_CONTROL
				ModAlt = 0x0004,				// GLFW_MOD_ALT
				ModSuper = 0x0008,				// GLFW_MOD_SUPER
			};
			const char* GetKeyName(eKey key, int scancode);
		}

		namespace Window
		{
			enum eHintsFramebuffer
			{
				RedBits = 0x00021001,				// GLFW_RED_BITS
				GreenBits = 0x00021002,				// GLFW_GREEN_BITS
				BlueBits = 0x00021003,				// GLFW_BLUE_BITS
				AlphaBits = 0x00021004,				// GLFW_ALPHA_BITS
				DepthBits = 0x00021005,				// GLFW_DEPTH_BITS
				StencilBits = 0x00021006,				// GLFW_STENCIL_BITS
				AccumRedBits = 0x00021007,				// GLFW_ACCUM_RED_BITS
				AccumGreenBits = 0x00021008,				// GLFW_ACCUM_GREEN_BITS
				AccumBlueBits = 0x00021009,				// GLFW_ACCUM_BLUE_BITS
				AccumAlphaBits = 0x0002100A,				// GLFW_ACCUM_ALPHA_BITS
				AuxBuffers = 0x0002100B,				// GLFW_AUX_BUFFERS
				Stereo = 0x0002100C,				// GLFW_STEREO
				Samples = 0x0002100D,				// GLFW_SAMPLES
				SrgbCapable = 0x0002100E,				// GLFW_SRGB_CAPABLE
				RefreshRate = 0x0002100F,				// GLFW_REFRESH_RATE
				Doublebuffer = 0x00021010,				// GLFW_DOUBLEBUFFER
			} eHintsFramebuffer;

			enum eHintsContext
			{
				ClientApi = 0x00022001,				// GLFW_CLIENT_API
				ContextVersionMajor = 0x00022002,				// GLFW_CONTEXT_VERSION_MAJOR
				ContextVersionMinor = 0x00022003,				// GLFW_CONTEXT_VERSION_MINOR
				ContextRevision = 0x00022004,				// GLFW_CONTEXT_REVISION
				ContextRobustness = 0x00022005,				// GLFW_CONTEXT_ROBUSTNESS
				OpenglForwardCompat = 0x00022006,				// GLFW_OPENGL_FORWARD_COMPAT
				OpenglDebugContext = 0x00022007,				// GLFW_OPENGL_DEBUG_CONTEXT
				OpenglProfile = 0x00022008,				// GLFW_OPENGL_PROFILE
				ContextReleaseBehavior = 0x00022009,				// GLFW_CONTEXT_RELEASE_BEHAVIOR
				ContextNoError = 0x0002200A,				// GLFW_CONTEXT_NO_ERROR
				ContextCreationApi = 0x0002200B,				// GLFW_CONTEXT_CREATION_API

			} eHintsContext;

			enum eWindowAttributes
			{
				Focused = 0x00020001,				// GLFW_FOCUSED
				Iconified = 0x00020002,				// GLFW_ICONIFIED
				Resizable = 0x00020003,				// GLFW_RESIZABLE
				Visible = 0x00020004,				// GLFW_VISIBLE
				Decorated = 0x00020005,				// GLFW_DECORATED
				AutoIconify = 0x00020006,				// GLFW_AUTO_ICONIFY
				Floating = 0x00020007,				// GLFW_FLOATING
				Maximized = 0x00020008,				// GLFW_MAXIMIZED
			} eWindowAttributes;

			typedef enum eHintsContext eContextAttributes;	// Hints and Attributes the same

			enum eAPI
			{
				NoApi = 0,				// GLFW_NO_API
				OpenglApi = 0x00030001,				// GLFW_OPENGL_API
				OpenglEsApi = 0x00030002,				// GLFW_OPENGL_ES_API
			} eAPI;

			enum eRobustness
			{
				NoRobustness = 0,				// GLFW_NO_ROBUSTNESS
				NoResetNotification = 0x00031001,				// GLFW_NO_RESET_NOTIFICATION
				LoseContextOnReset = 0x00031002,				// GLFW_LOSE_CONTEXT_ON_RESET

			} eRobustness;
			enum eProfile
			{
				OpenglAnyProfile = 0,				// GLFW_OPENGL_ANY_PROFILE
				OpenglCoreProfile = 0x00032001,				// GLFW_OPENGL_CORE_PROFILE
				OpenglCompatProfile = 0x00032002,				// GLFW_OPENGL_COMPAT_PROFILE
			} eProfile;

			enum eReleaseBehaviour
			{
				AnyReleaseBehavior = 0,				// GLFW_ANY_RELEASE_BEHAVIOR
				ReleaseBehaviorFlush = 0x00035001,				// GLFW_RELEASE_BEHAVIOR_FLUSH
				ReleaseBehaviorNone = 0x00035002,				// GLFW_RELEASE_BEHAVIOR_NONE

			} eReleaseBehaviour;
			enum eContextCreationAPI
			{
				NativeContextApi = 0x00036001,				// GLFW_NATIVE_CONTEXT_API
				EglContextApi = 0x00036002,				// GLFW_EGL_CONTEXT_API
			} eContextCreationAPI;

			enum eInputMode
			{
				Cursor = 0x00033001,				// GLFW_CURSOR
				StickyKeys = 0x00033002,				// GLFW_STICKY_KEYS
				StickyMouseButtons = 0x00033003,				// GLFW_STICKY_MOUSE_BUTTONS
				CursorNormal = 0x00034001,				// GLFW_CURSOR_NORMAL
				CursorHidden = 0x00034002,				// GLFW_CURSOR_HIDDEN
				CursorDisabled = 0x00034003,				// GLFW_CURSOR_DISABLED
			} eMode;


			typedef void (*windowposfun)(window*, int, int);
			typedef void (*windowsizefun)(window*, int, int);
			typedef void (*windowclosefun)(window*);
			typedef void (*windowrefreshfun)(window*);
			typedef void (*windowfocusfun)(window*, int);
			typedef void (*windowiconifyfun)(window*, int);
			typedef void (*framebuffersizefun)(window*, int, int);
			typedef void (*mousebuttonfun)(window*, int, int, int);
			typedef void (*cursorposfun)(window*, double, double);
			typedef void (*cursorenterfun)(window*, int);
			typedef void (*scrollfun)(window*, double, double);
			typedef void (*keyfun)(window*, int, int, int, int);
			typedef void (*charfun)(window*, unsigned int);
			typedef void (*charmodsfun)(window*, unsigned int, int);
			typedef void (*dropfun)(window*, int, const char**);

			//				VkResult CreateWindowSurface(VkInstance instance, window* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface);
			cursorenterfun SetCursorEnterCallback(window* window, cursorenterfun cbfun);
			cursorposfun SetCursorPosCallback(window* window, cursorposfun cbfun);
			dropfun SetDropCallback(window* window, dropfun cbfun);
			framebuffersizefun SetFramebufferSizeCallback(window* window, framebuffersizefun cbfun);
			int GetInputMode(window* window, int mode);
			int GetKey(window* window, int key);
			int GetMouseButton(window* window, int button);
			//				int GetPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily);
			int GetWindowAttrib(window* window, int attrib);
			int WindowShouldClose(window* window);
			keyfun SetKeyCallback(window* window, keyfun cbfun);
			monitor* GetWindowMonitor(window* window);
			mousebuttonfun SetMouseButtonCallback(window* window, mousebuttonfun cbfun);
			scrollfun SetScrollCallback(window* window, scrollfun cbfun);
			void DefaultWindowHints(void);
			void DestroyWindow(window* window);
			void FocusWindow(window* window);
			void GetCursorPos(window* window, double* xpos, double* ypos);
			void GetFramebufferSize(window* window, int* width, int* height);
			void GetWindowFrameSize(window* window, int* left, int* top, int* right, int* bottom);
			void GetWindowPos(window* window, int* xpos, int* ypos);
			void GetWindowSize(window* window, int* width, int* height);
			void HideWindow(window* window);
			void IconifyWindow(window* window);
			void MakeContextCurrent(window* window);
			void MaximizeWindow(window* window);
			void RestoreWindow(window* window);
			void SetClipboardString(window* window, const char* string);
			void SetCursor(window* window, cursor* cursor);
			void SetCursorPos(window* window, double xpos, double ypos);
			void SetInputMode(window* window, int mode, int value);
			void SetWindowAspectRatio(window* window, int numer, int denom);
			void SetWindowIcon(window* window, int count, const image* images);
			void SetWindowMonitor(window* window, monitor* monitor, int xpos, int ypos, int width, int height, int refreshRate);
			void SetWindowPos(window* window, int xpos, int ypos);
			void SetWindowShouldClose(window* window, int value);
			void SetWindowSize(window* window, int width, int height);
			void SetWindowSizeLimits(window* window, int minwidth, int minheight, int maxwidth, int maxheight);
			void SetWindowTitle(window* window, const char* title);
			void SetWindowUserPointer(window* window, void* pointer);
			void ShowWindow(window* window);
			void SwapBuffers(window* window);
			void* GetWindowUserPointer(window* window);
			void WindowHint(int hint, int value);
			windowclosefun SetWindowCloseCallback(window* window, windowclosefun cbfun);
			windowfocusfun SetWindowFocusCallback(window* window, windowfocusfun cbfun);
			windowiconifyfun SetWindowIconifyCallback(window* window, windowiconifyfun cbfun);
			windowposfun SetWindowPosCallback(window* window, windowposfun cbfun);
			windowrefreshfun SetWindowRefreshCallback(window* window, windowrefreshfun cbfun);
			windowsizefun SetWindowSizeCallback(window* window, windowsizefun cbfun);
		} // Window

		// 
		// Monitor
		//
		namespace Monitor
		{
			typedef struct gammaramp
			{
				unsigned short* red;
				unsigned short* green;
				unsigned short* blue;
				unsigned int size;
			} gammaramp;
			typedef struct vidmode
			{
				int width;
				int height;
				int redBits;
				int greenBits;
				int blueBits;
				int refreshRate;
			} vidmode;
			typedef void (*monitorfun)(monitor*, int);

			const char* GetMonitorName(monitor* monitor);
			const gammaramp* GetGammaRamp(monitor* monitor);
			const vidmode* GetVideoMode(monitor* monitor);
			const vidmode* GetVideoModes(monitor* monitor, int* count);
			monitor* GetPrimaryMonitor(void);
			monitor** GetMonitors(int* count);
			void GetMonitorPhysicalSize(monitor* monitor, int* widthMM, int* heightMM);
			void GetMonitorPos(monitor* monitor, int* xpos, int* ypos);
			void SetGamma(monitor* monitor, float gamma);
			void SetGammaRamp(monitor* monitor, const gammaramp* ramp);
			monitorfun SetMonitorCallback(monitorfun cbfun);
			window* CreateWindow(int width, int height, const char* title, monitor* monitor, window* share);
			window* GetCurrentContext(void);
		}	// Monitor

		//
		// Joystick
		//
		namespace Joystick
		{
			enum eJoystick
			{
				Joystick_1 = 0,				// GLFW_JOYSTICK_1
				Joystick_2 = 1,				// GLFW_JOYSTICK_2
				Joystick_3 = 2,				// GLFW_JOYSTICK_3
				Joystick_4 = 3,				// GLFW_JOYSTICK_4
				Joystick_5 = 4,				// GLFW_JOYSTICK_5
				Joystick_6 = 5,				// GLFW_JOYSTICK_6
				Joystick_7 = 6,				// GLFW_JOYSTICK_7
				Joystick_8 = 7,				// GLFW_JOYSTICK_8
				Joystick_9 = 8,				// GLFW_JOYSTICK_9
				Joystick_10 = 9,				// GLFW_JOYSTICK_10
				Joystick_11 = 10,				// GLFW_JOYSTICK_11
				Joystick_12 = 11,				// GLFW_JOYSTICK_12
				Joystick_13 = 12,				// GLFW_JOYSTICK_13
				Joystick_14 = 13,				// GLFW_JOYSTICK_14
				Joystick_15 = 14,				// GLFW_JOYSTICK_15
				Joystick_16 = 15,				// GLFW_JOYSTICK_16
				JoystickLast = Joystick_16,				// GLFW_JOYSTICK_LAST
			} eJoystick;

			typedef void (*joystickfun)(int, int);
			const char* GetJoystickName(int joy);
			const float* GetJoystickAxes(int joy, int* count);
			const unsigned char* GetJoystickButtons(int joy, int* count);
			int JoystickPresent(int joy);
			joystickfun SetJoystickCallback(joystickfun cbfun);
		}

		namespace Mouse
		{
			enum eMouse
			{
				MouseButton_1 = 0,				// GLFW_MOUSE_BUTTON_1
				MouseButton_2 = 1,				// GLFW_MOUSE_BUTTON_2
				MouseButton_3 = 2,				// GLFW_MOUSE_BUTTON_3
				MouseButton_4 = 3,				// GLFW_MOUSE_BUTTON_4
				MouseButton_5 = 4,				// GLFW_MOUSE_BUTTON_5
				MouseButton_6 = 5,				// GLFW_MOUSE_BUTTON_6
				MouseButton_7 = 6,				// GLFW_MOUSE_BUTTON_7
				MouseButton_8 = 7,				// GLFW_MOUSE_BUTTON_8
				MouseButtonLast = MouseButton_8,				// GLFW_MOUSE_BUTTON_LAST
				MouseButtonLeft = MouseButton_1,				// GLFW_MOUSE_BUTTON_LEFT
				MouseButtonRight = MouseButton_2,				// GLFW_MOUSE_BUTTON_RIGHT
				MouseButtonMiddle = MouseButton_3,				// GLFW_MOUSE_BUTTON_MIDDLE

			} eMouse;
		}

		namespace Error
		{
			enum eError
			{
				NotInitialized = 0x00010001,				// GLFW_NOT_INITIALIZED
				NoCurrentContext = 0x00010002,				// GLFW_NO_CURRENT_CONTEXT
				InvalidEnum = 0x00010003,				// GLFW_INVALID_ENUM
				InvalidValue = 0x00010004,				// GLFW_INVALID_VALUE
				OutOfMemory = 0x00010005,				// GLFW_OUT_OF_MEMORY
				ApiUnavailable = 0x00010006,				// GLFW_API_UNAVAILABLE
				VersionUnavailable = 0x00010007,				// GLFW_VERSION_UNAVAILABLE
				PlatformError = 0x00010008,				// GLFW_PLATFORM_ERROR
				FormatUnavailable = 0x00010009,				// GLFW_FORMAT_UNAVAILABLE
				NoWindowContext = 0x0001000A,				// GLFW_NO_WINDOW_CONTEXT
			} eError;
			typedef void (*errorfun)(int, const char*);
			errorfun SetErrorCallback(errorfun cbfun);
		}
		namespace Cursor
		{
			enum eShape
			{
				ArrowCursor = 0x00036001,				// GLFW_ARROW_CURSOR
				IbeamCursor = 0x00036002,				// GLFW_IBEAM_CURSOR
				CrosshairCursor = 0x00036003,				// GLFW_CROSSHAIR_CURSOR
				HandCursor = 0x00036004,				// GLFW_HAND_CURSOR
				HresizeCursor = 0x00036005,				// GLFW_HRESIZE_CURSOR
				VresizeCursor = 0x00036006,				// GLFW_VRESIZE_CURSOR
			};
			void DestroyCursor(cursor* cursor);
			cursor* CreateCursor(const image* image, int xhot, int yhot);
			cursor* CreateStandardCursor(eShape shape);
		}

		//
		// System
		//
		namespace System
		{
			const char* GetVersionString(void);
			const char** GetRequiredInstanceExtensions(uint32_t* count);
			double GetTime(void);
			glproc GetProcAddress(const char* procname);
			int ExtensionSupported(const char* extension);
			int Init(void);
			int VulkanSupported(void);
			uint64_t GetTimerFrequency(void);
			uint64_t GetTimerValue(void);
			//				vkproc GetInstanceProcAddress(VkInstance instance, const char* procname);
			void GetVersion(int* major, int* minor, int* rev);
			void PollEvents(void);
			void PostEmptyEvent(void);
			void SetTime(double time);
			void SwapInterval(int interval);
			void Terminate(void);
			void WaitEvents(void);
			void WaitEventsTimeout(double timeout);
		}	 // System
	}
}

