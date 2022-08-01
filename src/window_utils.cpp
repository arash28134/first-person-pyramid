#include "window_utils.h"

#include <string>

#include "stb_image.h"

void window_utils::SetWindowIcon(GLFWwindow *window, std::string fileName){
    GLFWimage images[1];

	images[0].pixels = stbi_load(fileName.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels 

	glfwSetWindowIcon(window, 1, images); 

	stbi_image_free(images[0].pixels);
}