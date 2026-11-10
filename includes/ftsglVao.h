#ifndef FTSGL_VAO_H
# define FTSGL_VAO_H

# define GLEW_STATIC
# include <GL/glew.h>

typedef struct s_ftsglVao
{
	GLuint	addr;
}	t_ftsglVao;

t_ftsglVao	ftsglVaoGen();

t_ftsglVao	*ftsglVaoBind(t_ftsglVao *vao);

void	ftsglVaoDestroy(t_ftsglVao *vao);

#endif
