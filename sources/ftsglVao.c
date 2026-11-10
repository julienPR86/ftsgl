#include "ftsglVao.h"

t_ftsglVao ftsglVaoGen()
{
	t_ftsglVao	vao;

	glGenVertexArrays(1, &vao.addr);
	return (vao);
}

t_ftsglVao *ftsglVaoBind(t_ftsglVao *vao)
{
	if (NULL == vao)
		return (NULL);
	glBindVertexArray(vao->addr);
	return (vao);
}

void	ftsglVaoDestroy(t_ftsglVao *vao)
{
	if (NULL == vao)
		return ;
	glDeleteVertexArrays(1, &vao->addr);
	return ;
}
