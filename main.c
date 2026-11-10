#define LIBSTR_IMPLEMENTATION
#include "libftsgl.h"
#include "ftsglVao.h"

int	width = 540;
int	height = 540;

int	main(void)
{
	t_ftsglWindow	*window = ftsglWindowCreate(width, height, "ftsgl");
	if (NULL == window)
		return (FTSGL_FAILURE);

	t_ftsglRenderer	*renderer = ftsglRendererCreate(window);
	GLint	us = glGetUniformLocation(renderer->program->addr, "resolution");
	glUniform2f(us, window->width, window->height);
	int	x = 0;
	while(!glfwWindowShouldClose(window->win))
	{
        glfwGetWindowSize(window->win, &width, &height);
		glUniform2f(us, width, height);

		glfwPollEvents();
		ftsglRendererSetPixelColor(renderer, x % window->width, x / window->width, (t_ftsglVec3){1, 0, 0});
		++x;
		if (x >= window->width * window->height)
			x = 0;
		ftsglRendererPresent(renderer);
	}
	ftsglRendererDestroy(renderer);
	ftsglWindowDestroy(window);
	return (FTSGL_SUCCESS);
}
