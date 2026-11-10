#ifndef FTSGL_WINDOW_H
# define FTSGL_WINDOW_H

# include <stdio.h>
# include <stdlib.h>

# define GLEW_STATIC
# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include "ftsglVao.h"

typedef struct s_ftsglWindow
{
	int			width;
	int			height;
	t_ftsglVao	vao;
	char		*title;
	GLFWwindow	*win;
}	t_ftsglWindow;

t_ftsglWindow	*ftsglWindowCreate(int width, int height, char *title);

void	ftsglWindowDestroy(t_ftsglWindow *window);

#endif
