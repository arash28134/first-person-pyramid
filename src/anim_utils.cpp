#include "anim_utils.h"

void anim_utils::DrawMovingAnim(bool *direction, float *offset, float *maxOffset, float *increment){
    if (*direction){
    *offset += *increment;
    } 
    else {
        *offset -= *increment;
    }

    if (abs(*offset) >= *maxOffset) {
        *direction = !*direction;
    }
}

void anim_utils::DrawRotatingAnim(float *curAngle, float incrAngle){
    *curAngle += incrAngle;
    
    if(*curAngle >= 360.0f){
        *curAngle -= 360.0f;
    }
}

void anim_utils::DrawScalingAnim(bool *scaleDir, float *curSize, float incrSize, float maxSize, float minSize){
    if(*scaleDir){
        *curSize += incrSize;
    }
    else{
        *curSize -= incrSize;
    }

    if(*curSize >= maxSize || *curSize <= minSize){
        *scaleDir = !*scaleDir;
    }
}