#ifndef FTSGL_VECTOR_H
# define FTSGL_VECTOR_H

# define GLEW_STATIC
# include <GL/glew.h>

typedef struct s_ftsglVector2D
{
	GLfloat	x;
	GLfloat	y;
}	t_ftsglVec2;

typedef struct s_ftsglVector3D
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;
}	t_ftsglVec3;

typedef struct s_ftsglVector4D
{
	GLfloat	x;
	GLfloat	y;
	GLfloat	z;
	GLfloat	w;
}	t_ftsglVec4;

t_ftsglVec2	ftsglVec2(GLfloat x, GLfloat y);

t_ftsglVec3	ftsglVec3(GLfloat x, GLfloat y, GLfloat z);

t_ftsglVec4	ftsglVec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

#endif
