#pragma once

#include <string>

#include <GLFW/glfw3.h>

class window_utils
{
public:
    // WARNING: OBSOLETE FUNCTION
    static void SetWindowIcon(GLFWwindow *window, std::string fileName);
};