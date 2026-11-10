#include "ftsglWindow.h"

void	error_callback(int error, const char *description);
void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
void	window_close_callback(GLFWwindow *window);

t_ftsglWindow	*ftsglWindowCreate(int width, int height, char *title)
{
	t_ftsglWindow	*window;

	glfwSetErrorCallback(error_callback);

	if (GLFW_FALSE == glfwInit())
		return (NULL);

	window = malloc(sizeof(t_ftsglWindow));
	if (NULL == window)
	{
		glfwTerminate();
		return (NULL);
	}
	window->width = width;
	window->height = height;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window->win = glfwCreateWindow(width, height, title, NULL, NULL);
	if (NULL == window->win)
	{
		ftsglWindowDestroy(window);
		return (NULL);
	}
	
	int	maj = glfwGetWindowAttrib(window->win, GLFW_CONTEXT_VERSION_MAJOR);
	int	min = glfwGetWindowAttrib(window->win, GLFW_CONTEXT_VERSION_MINOR);
	printf("OpenGl version: %d.%d\n", maj, min);

	glfwSetKeyCallback(window->win, key_callback);
	glfwSetWindowCloseCallback(window->win, window_close_callback);
	glfwMakeContextCurrent(window->win);
	glfwSwapInterval(0);

	glewExperimental = GL_TRUE;
	GLenum	glewStatus = glewInit();
	if (GLEW_OK != glewStatus && GLEW_ERROR_NO_GLX_DISPLAY != glewStatus)
	{
		printf("Error: %s\n", glewGetErrorString(glewStatus));
		ftsglWindowDestroy(window);
		return (NULL);
	}

	window->vao = ftsglVaoGen();
	ftsglVaoBind(&window->vao);
	return (window);
}

void	ftsglWindowDestroy(t_ftsglWindow *window)
{
	if (NULL == window)
		return ;
	ftsglVaoDestroy(&window->vao);
	glfwDestroyWindow(window->win);
	glfwTerminate();
	free(window);
	return ;
}
