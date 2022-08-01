#pragma once

#include <iostream>
#include <string.h>

#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class anim_utils
{
private:
public:
    // draw moving animation
    static void DrawMovingAnim(bool *direction, float *offset, float *maxOffset, float *increment);

    // draw rotating animation
    static void DrawRotatingAnim(float *curAngle, float incrAngle);

    // draw scaling animation
    static void DrawScalingAnim(bool *scaleDir, float *curSize, float incrSize, float maxSize, float minSize);
};