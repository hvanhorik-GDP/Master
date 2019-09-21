#pragma once

#include "glfw_raw/glfw_raw_Window.h"
#include "glfw_raw/glfw_raw_Error.h"

void key_callback(glfw::raw::window* window, int key, int scancode, int action, int mods);

void error_callback(glfw::raw::Error::eError error, const char* description);