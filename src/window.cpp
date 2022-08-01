#include "window.h"

Window::Window()
{
	width = 800;
	height = 600;

	resizable = false;

	bufferWidth = 0, bufferHeight = 0;

	mainWindow = 0;

	for(size_t i = 0; i < 1024; i++){
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight, bool windowResizable)
{
	width = windowWidth;
	height = windowHeight;

	resizable = windowResizable;

	bufferWidth = 0, bufferHeight = 0;

	mainWindow = 0;

	for(size_t i = 0; i < 1024; i++){
		keys[i] = 0;
	}
}

int Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "GLFW library load failed...\n";
		glfwTerminate();
		return 1;
	}

	// Setup GLFW Window properties
	// OpenGL Version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL profile without backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OpenGL profile allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// OpenGL profile window resizability
	if (resizable){
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
	else{
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	// create the window
	mainWindow = glfwCreateWindow(width, height, "Main window", NULL, NULL);
	if (!mainWindow)
	{
		std::cerr << "GLFW window creation failed...\n";
		glfwTerminate();
		return 1;
	}

	// OpenGL viewport dimensions
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set context for GLEW to use
	glfwMakeContextCurrent(mainWindow);

	// create callbacks for keyboard and mouse
	createCallbacks();

	// lock the cursor
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// allow the use of modern OpenGL extension
	glewExperimental = GLU_TRUE;

	GLenum error = glewInit();
	if (error != GLEW_OK)
	{
		std::cerr << "GLEW initialization failed...\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// enable depth
	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);

	return 0;
}

void Window::createCallbacks(){
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange(){
	GLfloat theChange = xChange;
	xChange = 0.0f;

	return theChange;
}

GLfloat Window::getYChange(){
	GLfloat theChange = yChange;
	yChange = 0.0f;

	return theChange;
}

void Window::handleKeys(GLFWwindow* _window, int _key, int _code, int _action, int _mode){
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(_window));

	if(_key == GLFW_KEY_ESCAPE && _action == GLFW_PRESS){
		glfwSetWindowShouldClose(_window, GL_TRUE);
	}

	if(_key >= 0 && _key < 1024){
		if(_action == GLFW_PRESS){
			theWindow->keys[_key] = true;
		}
		else if(_action == GLFW_RELEASE){
			theWindow->keys[_key] = false;
		}
	}
}

void Window::handleMouse(GLFWwindow* _window, double xPos, double yPos){
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(_window));

	if(theWindow->mouseFirstMove){
	    theWindow->lastX = xPos;
		theWindow->lastY = yPos;

		theWindow->mouseFirstMove = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}