#include "ftsglWindow.h"

void	key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	(void)window;
	(void)scancode;
	(void)action;
	(void)mods;
	printf("Key %d pressed\n", key);
	return ;
}
