#include "ftsglWindow.h"

void	window_close_callback(GLFWwindow *window)
{
	(void)window;
	printf("Window closed\n");
	return ;
}
