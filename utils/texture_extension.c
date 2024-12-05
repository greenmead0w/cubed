

#include "utils.h"


char texture_extension(char *line, char *start, int fd)
{
	int path_len;

	path_len = line - start;
	if (path_len < 4 || ft_strncmp(line - 4, ".xpm", 4) != 0)
	{
		close(fd);
		return (-1);
	}
	return (0);
}