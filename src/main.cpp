// system libraries
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

// glew library
#include <GL/glew.h>

// glfw library
#include <GLFW/glfw3.h>

// glm libraries
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, identity
#include <glm/gtc/type_ptr.hpp>

// stb library
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// user defined base libraries
#include "window.h"
#include "mesh.h"
#include "shader.h"
#include "shaders.h"
#include "camera.h"

// user defined util libraries
#include "window_utils.h"
#include "mesh_utils.h"
#include "anim_utils.h"

// namespaces
using namespace std;

// main window
Window mainWindow;

// main camera
camera mainCamera;

// delta variables
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// list of meshes
std::vector<Mesh*> meshList;

// list of shaders
std::vector<Shader> shaderList;

// pyramid current angle animation variable
float pyramid_curAngle = 0.0f;

// functions
void CreateMeshes();
void CreateShaders();

int main()
{
	// initialize the main window
	mainWindow.initialize();

	CreateMeshes();
	CreateShaders();

	// initialize main camera
	mainCamera = camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 4.0f, 0.5f, 3.7f);

	// uniform variables	
	GLuint uniformModel, uniformProjection, uniformView;

	// perspective projection, used for rendering 3d scenes
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Loop until windows closed
	while (!mainWindow.getShouldClose())
	{
		// deltatime calculations
		GLfloat currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// get and handle user inputs
		glfwPollEvents();

		// control key press
		mainCamera.keyControl(mainWindow.getKeys(), deltaTime);

		// control mouse movements
		mainCamera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		
		// clear the window with black color. we can set this to any rgba value (between 0 and 1)
		// and get a different color. for instance we could say:
		// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// and we'd have the blue color as our screen color (we'd see a blue color around the pyramid)
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// use pyramid shader's program
		shaderList[0].UseShader();

		// set uniform variables to uniform locations in shader
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();

		// draw rotating animation for pyramid
		anim_utils::DrawRotatingAnim(&pyramid_curAngle, 0.5f);

		// identity matrix
		glm::mat4 model = glm::mat4(1.0f);

		// apply translate, scale and rotation to identity matrix 
		model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
		model = glm::rotate(model, glm::radians(pyramid_curAngle), glm::vec3(0.0f, 1.0f, 0.0f));

		// set uniform variables using their uniform address
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.calculateViewMatrix()));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		
		// render all meshes
		mesh_utils::RenderMeshList(meshList);
		
		glUseProgram(0);

		// swap main window's buffers. this is a very important part of render loop which is done
		// at the end
		mainWindow.swapBuffers();
	}

	return 0;
}

void CreateMeshes(){
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        0.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, -1.0f, -1.0f
    };

    unsigned int indices[] = {
        0, 3, 1, 
        1, 3, 2,
        2, 3, 4,
        4, 3, 0,
        0, 1, 2,
		2, 4, 0
    };

	// create a new object of mesh class (pyramid) and make a pointer to it
	Mesh* pyramid = new Mesh();
	pyramid->CreateMesh(vertices, indices, 15, 18);

	// add mesh (pyramid) to the mesh list
	meshList.push_back(pyramid);
}

void CreateShaders()
{
	// create a new object of shader class (pyramid's shader) and make a pointer to it
	Shader* pyramid_shader = new Shader();
	pyramid_shader->CreateProgram(shaders::pyramid_vShader, shaders::pyramid_fShader);

	// add it to the shader list
	shaderList.push_back(*pyramid_shader);
}