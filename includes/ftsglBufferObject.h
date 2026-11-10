#ifndef FTSGL_BUFFER_OBJECT_H
# define FTSGL_BUFFER_OBJECT_H

# include <stdlib.h>

# define GLEW_STATIC
# include <GL/glew.h>
# include "ftsglQuad.h"
# include "libstr.h"

typedef struct s_ftsglBufferObject
{
	GLuint		addr;
	GLenum		type;
	void		*data;
	GLsizeiptr	size;
	GLsizeiptr	capacity;
}	t_ftsglBufferObject;

t_ftsglBufferObject	ftsglBufferObjectGen(GLenum type, GLsizeiptr size);

t_ftsglBufferObject	*ftsglBufferObjectDataAdd(t_ftsglBufferObject *buffer, GLsizeiptr size, const void *data);

t_ftsglBufferObject	*ftsglBufferObjectDataUpdate(t_ftsglBufferObject *buffer, GLsizeiptr offset, GLsizeiptr size, const void *data);

t_ftsglBufferObject	*ftsglBufferObjectSync(t_ftsglBufferObject *buffer);

void	ftsglBufferObjectDestroy(t_ftsglBufferObject *buffer);

#endif
