#include "ftsglWindow.h"

void	error_callback(int error, const char *description)
{
	fprintf(stderr, "Error %d : %s\n", error, description);
	return ;
}
