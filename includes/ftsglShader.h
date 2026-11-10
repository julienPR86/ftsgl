#ifndef FTSGL_SHADER_H
# define FTSGL_SHADER_H

# include <stdio.h>
# include <stdlib.h>
# define GLEW_STATIC
# include <GL/glew.h>
# include "utils.h"

typedef struct s_ftsglShader
{
	GLenum	type;
	GLint	addr;
	char	*path;
}	t_ftsglShader;

typedef struct s_ftsglShaderProgramAttribute
{
	GLint	addr;
	GLenum	type;
	GLint	attr_size;
	GLsizei	vertex_size;
	GLchar	*name;
	void	*offset;
} t_ftsglShaderProgramAttribute;

typedef struct s_ftsglShaderProgram
{
	GLuint							addr;
	GLuint							colindex;
	GLsizei							attr_count;
	GLsizei							shaders_count;
	GLchar							*colname;
	t_ftsglShaderProgramAttribute	**attributes;
	t_ftsglShader					**shaders;
}	t_ftsglShaderProgram;

t_ftsglShaderProgram	*ftsglProgramCreate(GLint n, t_ftsglShader **shaders, GLuint colindex, const GLchar *colname);

t_ftsglShaderProgram	*ftsglProgramReload(t_ftsglShaderProgram *program);

t_ftsglShaderProgram	*ftsglProgramUse(t_ftsglShaderProgram *program);

t_ftsglShaderProgram	*ftsglProgramAttributeAdd(t_ftsglShaderProgram *program, const GLchar *name, GLenum type, GLint attr_size, GLsizei vertex_size, const void *offset);

void	ftsglProgramDestroy(t_ftsglShaderProgram *program);

t_ftsglShader	*ftsglShaderLoad(const char *path, GLenum type);

t_ftsglShader	*ftsglShaderReload(t_ftsglShader *shader);

void	ftsglShaderDestroy(t_ftsglShader *shader);

t_ftsglShaderProgramAttribute	*ftsglProgramAttributeGen(t_ftsglShaderProgram *program, const GLchar *name, GLenum type, GLint attr_size, GLsizei vertex_size, const void *offset);

void	ftsglProgramAttributeDestroy(t_ftsglShaderProgramAttribute *attrib);

#endif
