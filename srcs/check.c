/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:34:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/19 21:05:51 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"


static char	read_lines(int fd, char *line, t_game *game, \
		t_track_items *track_elements)
{
	while (line)
	{
		line = get_next_line(fd); // no estamos diferenciando si gnl devuelve nulo for EOF o por problemas de read() no?
		//printf("line[%d] is: %s\n", i++, line);
		if (line)
		{
			if (examine_line(line, game, track_elements))
			{
				close(fd);
				free_simple_pointer(line);
				return (-1);
			}
			free_simple_pointer(line);
		}
	}
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
		perror("Error opening a file"); //mantenemos perror o añadimos nuestro error.h? (he añadido stdio.h para perror en cub3d.h)
		return (-1);
	}
	if (read_lines(fd, line, game, track_elements))
		return (-1);
	close(fd);
	return (0);
}

/*
** !!! TESTAR !!!
*/
static char	check_file_extension(char *file)
{
	char	*run;

	run = file;
	while (*run)
		run++;
	run--;
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
