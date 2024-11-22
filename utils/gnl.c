/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:26:39 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/22 18:37:11 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "definitions.h"

static char	*join_buffer(char *buff, int fd)
{
	int		chars_count;
	char	*line;
	char	*line1;

	chars_count = 1;
	line = ft_strdup(buff);
	if (!line)
		return (0);
	while (chars_count != 0 && !ft_strchr(line, '\n'))
	{
		chars_count = read(fd, buff, BUFFER_SIZE);
		if (chars_count == -1)
		{
			free(line);
			return (0);
		}
		buff[chars_count] = '\0';
		line1 = ft_strjoin(line, buff);
		free(line);
		line = line1;
	}
	return (line);
}

static void	is_there_nl(char *line, char *buff, char *nl_pos)
{
	int	end;

	if (nl_pos)
	{
		ft_strlcpy(buff, nl_pos + 1, BUFFER_SIZE + 1);
		end = nl_pos - line + 1;
	}
	else
	{
		ft_strlcpy(buff, "", BUFFER_SIZE + 1);
		end = ft_strlen(line);
	}
	line[end] = '\0';
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	char		*nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = join_buffer(buff, fd);
	if (!line || !*line)
	{
		if (line)
			free(line);
		return (0);
	}
	nl_pos = ft_strchr(line, '\n');
	is_there_nl(line, buff, nl_pos);
	return (line);
}
