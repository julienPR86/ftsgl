#include "ftsglShader.h"

t_ftsglShaderProgram	*ftsglProgramCreate(GLsizei n, t_ftsglShader **shaders, GLuint colindex, const GLchar *colname)
{
	t_ftsglShaderProgram	*program;

	program = malloc(sizeof(t_ftsglShaderProgram));
	if (NULL == program)
		return (NULL);
	program->addr = glCreateProgram();
	program->colname = strDup(colname);
	if ( 0 == program->addr || NULL == program->colname)
	{
		free(program->colname);
		free(program);
		return (NULL);
	}
	program->colindex = colindex;
	program->shaders = NULL;
	program->shaders_count = 0;
	if (NULL != shaders && NULL != *shaders && n > 0)
	{
		program->shaders_count = n;
		program->shaders = malloc(n * sizeof(t_ftsglShader *));
		if (NULL == program->shaders)
		{
			glDeleteProgram(program->addr);
			free(program);
			return (NULL);
		}
		strMemCopy(program->shaders, shaders, n * sizeof(t_ftsglShader *));
		for (GLsizei index = 0; index < n; ++index)
			glAttachShader(program->addr, (*(program->shaders + index))->addr);
	}
	program->attributes = NULL;
	program->attr_count = 0;
	glBindFragDataLocation(program->addr, colindex, colname);
	glLinkProgram(program->addr);
	return (program);
}

t_ftsglShaderProgram	*ftsglProgramReload(t_ftsglShaderProgram *program)
{
	if (NULL == program && NULL != program->shaders)
		return (NULL);
	for (GLsizei index = 0; index < program->shaders_count; ++index)
		ftsglShaderReload(*(program->shaders + index));
	glBindFragDataLocation(program->addr, program->colindex, program->colname);
	glLinkProgram(program->addr);
	return (program);
}

t_ftsglShaderProgram	*ftsglProgramUse(t_ftsglShaderProgram *program)
{
	if (NULL == program)
		return (NULL);
	glUseProgram(program->addr);
	return (program);
}

t_ftsglShaderProgram	*ftsglProgramAttributeAdd(t_ftsglShaderProgram *program, const GLchar *name, GLenum type, GLint attr_size, GLsizei vertex_size, const void *offset)
{
	t_ftsglShaderProgramAttribute	*attribute;
	t_ftsglShaderProgramAttribute	**old = program->attributes;

	if (NULL == program || NULL == name || vertex_size < 1)
		return (NULL);
	attribute = ftsglProgramAttributeGen(program, name, type, attr_size, vertex_size, offset);
	if (NULL == attribute)
		return (NULL);
	program->attributes = realloc(program->attributes, (program->attr_count + 1) * sizeof(t_ftsglShaderProgramAttribute *));
	if (NULL == program->attributes)
	{
		free(attribute);
		program->attributes = old;
		return (NULL);
	}
	*(program->attributes + program->attr_count) = attribute;
	++program->attr_count;
	glEnableVertexAttribArray(attribute->addr);
	return (program);
}

void	ftsglProgramDestroy(t_ftsglShaderProgram *program)
{
	if (NULL == program)
		return ;
	free(program->colname);
	for (GLsizei index = 0; index < program->attr_count; ++index)
		ftsglProgramAttributeDestroy(*(program->attributes + index));
	free(program->attributes);
	for (GLsizei index = 0; index < program->shaders_count; ++index)
	{
		glDetachShader(program->addr, (*(program->shaders + index))->addr);
		ftsglShaderDestroy(*(program->shaders + index));
	}
	free(program->shaders);
	glDeleteProgram(program->addr);
	program->attributes = NULL;
	program->shaders = NULL;
	free(program);
	return ;
}

static GLint	shaderGetStatus(t_ftsglShader *shader)
{
	GLint	status;

	glGetShaderiv(shader->addr, GL_COMPILE_STATUS, &status);
	return (status);
}

static void	shaderDisplayError(t_ftsglShader *shader)
{
	GLint	size;
	GLchar	*buffer;

	glGetShaderiv(shader->addr, GL_INFO_LOG_LENGTH, &size);
	buffer = malloc(size * sizeof(char));
	if (NULL == buffer)
		return ;
	glGetShaderInfoLog(shader->addr, size, NULL, buffer);
	printf("Error: Shader: %s\n", buffer);
	free(buffer);
	return ;
}

t_ftsglShader	*ftsglShaderLoad(const char *path, GLenum type)
{
	t_ftsglShader	*shader;

	shader = malloc(sizeof(t_ftsglShader));
	if (NULL == shader)
		return (NULL);
	shader->addr = glCreateShader(type);
	shader->type = type;
	shader->path = strDup(path);
	if (NULL == path)
	{
		free(shader);
		return (NULL);
	}
	if (NULL == ftsglShaderReload(shader))
	{
		free(shader);
		return (NULL);
	}
	return (shader);
}

t_ftsglShader	*ftsglShaderReload(t_ftsglShader *shader)
{
	GLint	status;
	char	*shaderText;

	if (0 == shader->addr)
		return (NULL);
	shaderText = read_file(shader->path);
	if (NULL == shaderText)
		return (NULL);
	glShaderSource(shader->addr, 1, (const char *const *)&shaderText, NULL);
	glCompileShader(shader->addr);
	free(shaderText);
	status = shaderGetStatus(shader);
	if (GL_TRUE != status)
	{
		shaderDisplayError(shader);
		return (NULL);
	}
	return (shader);
}

void	ftsglShaderDestroy(t_ftsglShader *shader)
{
	if (NULL == shader)
		return ;
	glDeleteShader(shader->addr);
	free(shader->path);
	shader->path = NULL;
	shader->addr = 0;
	shader->type = 0;
	free(shader);
	return ;
}

t_ftsglShaderProgramAttribute	*ftsglProgramAttributeGen(t_ftsglShaderProgram *program, const GLchar *name, GLenum type, GLint attr_size, GLsizei vertex_size, const void *offset)
{
	t_ftsglShaderProgramAttribute	*attrib;

	if (NULL == program || NULL == name || attr_size <= 0)
		return (NULL);
	attrib = malloc(sizeof(t_ftsglShaderProgramAttribute));
	if (NULL == attrib)
		return (NULL);
	attrib->name = strDup(name);
	attrib->addr = glGetAttribLocation(program->addr, name);
	if (NULL == attrib->name || attrib->addr < 0)
	{
		free(attrib->name);
		free(attrib);
		return (NULL);
	}
	glVertexAttribPointer(attrib->addr, attr_size, type, GL_FALSE, vertex_size, offset);
	attrib->type = type;
	attrib->attr_size = attr_size;
	attrib->vertex_size = vertex_size;
	attrib->offset = (void *)offset;
	return (attrib);
}

void	ftsglProgramAttributeDestroy(t_ftsglShaderProgramAttribute *attrib)
{
	if (NULL == attrib)
		return ;
	free(attrib->name);
	free(attrib);
	return ;
}
