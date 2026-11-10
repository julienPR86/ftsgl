#include "libftsgl.h"

char	*read_file(const char *path)
{
	const size_t	chunk_size = 256;
	int				fd;
	int				nread;
	char			*tmp = NULL;
	char			*content = NULL;

	if (NULL == path)
		return (NULL);
	if (0 != access(path, R_OK))
		return (NULL);
	fd = open(path, O_RDONLY);
	if (-1 == fd)
		return (NULL);
	while (1)
	{
		tmp = malloc(sizeof(char) * (chunk_size + 1));
		if (NULL == tmp)
		{
			free(content);
			close(fd);
			return (NULL);
		}
		nread = read(fd, tmp, chunk_size);
		if (-1 == nread)
		{
			free(tmp);
			free(content);
			close(fd);
			return (NULL);
		}
		if (0 == nread)
		{
			free(tmp);
			break ;
		}
		tmp[nread] = '\0';
		if (NULL == strAppend(&content, tmp))
		{
			free(tmp);
			free(content);
			close(fd);
			return (NULL);
		}
		free(tmp);
	}
	close(fd);
	return (content);
}
