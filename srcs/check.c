/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:34:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/26 20:18:45 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <fcntl.h>

static char	read_lines(int fd, char *line, t_game *game, \
		t_track_items *track_elements)
{
	int line_counter;

	line_counter = 0;
	while (line)
	{
		line = get_next_line(fd); // no estamos diferenciando si gnl devuelve nulo for EOF o por problemas de read() no?
		if (line)
		{
			if (examine_line(line, game, track_elements))
			{
				close(fd);
				free_simple_pointer(line);
				return (-1);
			}
			free_simple_pointer(line);
			line_counter++;
		}
	}
	if (!line_counter)
		return printf("empty_.cub_error\n");
	else if (!game->map_rows_counter)
		return printf("no_map_error\n");
	return (0);
}

static char	open_and_read_file_check(char *file, t_game *game, \
		t_track_items *track_elements)
{
	char	*line;
	int		fd;

	line = (char *) 1;
	fd = open(file, O_RDONLY, 0111); //parece que O_RDONLY no requiere 3er argumento, O_CREAT sí
	if (fd == -1)
	{
		write(2, OPEN_FILE, ft_strlen(OPEN_FILE));
		return (-1);
	}
	if (read_lines(fd, line, game, track_elements))
		return (-1);
	close(fd);
	return (0);
}

static char	check_file_extension(char *file)
{
	char	*run;

	run = file;
	while (*run)
		run++;
//	run--;
	while (run != file && *run != '.')
		run--;
	if (run == file || ft_strcmp(run, ".cub"))
	{
		write(2, WRONG_EXT, ft_strlen(WRONG_EXT));
		return (-1);
	}
	return (0);
}

/*
**	no he encontrado referencias a open_and_read_parse,
**	he supuesto que tiene la funcionalidad de parse() (se llama en main_cubed.c)
*/
char	check(char *file, t_game *game, t_track_items *track_elements)
{
	if (check_file_extension(file))
		return (-1);
	if (open_and_read_file_check(file, game, track_elements))
		return (-1);
	// if (open_and_read_parse(file, game))
	// 	return (-1);
	return (0);
}
