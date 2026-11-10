#include "ftsglBufferObject.h"

t_ftsglBufferObject	ftsglBufferObjectGen(GLenum type, GLsizeiptr size)
{
	t_ftsglBufferObject	buffer;

	buffer.type = type;
	buffer.capacity = size;
	buffer.size = 0;
	buffer.data = malloc(size);
	if (NULL == buffer.data)
		return ((t_ftsglBufferObject){0});
	glGenBuffers(1, &buffer.addr);
	glBindBuffer(type, buffer.addr);
	glBufferData(buffer.type, size, NULL, GL_DYNAMIC_DRAW);
	return (buffer);
}

t_ftsglBufferObject	*ftsglBufferObjectDataAdd(t_ftsglBufferObject *buffer, GLsizeiptr size, const void *data)
{
	if (NULL == buffer)
		return (NULL);
	if (buffer->size + size > buffer->capacity)
		return (NULL);
	strMemCopy(buffer->data + buffer->size, data, size);
	buffer->size += size;
	return (buffer);
}

t_ftsglBufferObject	*ftsglBufferObjectDataUpdate(t_ftsglBufferObject *buffer, GLsizeiptr offset, GLsizeiptr size, const void *data)
{
	if (NULL == buffer)
		return (NULL);
	if (offset + size > buffer->capacity)
		return (buffer);
	strMemCopy(buffer->data + offset, data, size);
	glBufferSubData(buffer->type, offset, size, data);
	return (buffer);
}

t_ftsglBufferObject	*ftsglBufferObjectSync(t_ftsglBufferObject *buffer)
{
	if (NULL == buffer)
		return (NULL);
	glBufferSubData(buffer->type, 0, buffer->size, buffer->data);
	return (buffer);
}

void	ftsglBufferObjectDestroy(t_ftsglBufferObject *buffer)
{
	if (NULL == buffer)
		return ;
	free(buffer->data);
	glDeleteBuffers(1, &buffer->addr);
	buffer->addr = 0;
	return ;
}
