/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:54:08 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 21:37:14 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cubed.h>
#include <fnctl.h>

static char    parse_items(char *line, t_game *game)
{
	char	result;
	char	*run;

	result = -1;
	run = line;
	if (!line)
		return (-1);
	if (*line == '\n')
		return (0);
	while (*run == ' ')
		run++;
	if (*run == 'F' || *run == 'C')
		result = fill_colors_list(run, game);
	else if (!compare_to_all_textures(run))
		result = fill_textures_matrix(run, game);
	else if (*run == '1')
		result = fill_map(line);
	else
		write(2, WRONG_FILE, ft_strlen(WRONG_FILE));
	if (result)
		return (-1);
	return (0);
}

static char	read_lines(int fd, char *line, t_game *game)
{
	while (line)
	{
		line = gnl(fd);
		if (line)
		{
			if (parse_items(line, game))
			{
				close(fd);
				free_simple_pointer(line);
				write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
				return (-1);
			}
			free_simple_pointer(line);
		}
	}
	return (0);
}

static char	initialize_map_matrix(t_game *game)
{
	game->map = malloc(sizeof(void *) * (game->map_rows_counter + 1))
	if (!game->map)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	game->map[game->map_rows_counter] = (void *) 0;
}

char	parse(char *file, t_game *game)
{
	char	*line;
	int		fd;

	if (initialize_map_matrix(game))
		return (-1);
	line = (char *) 1;
	fd = open(file, O_RDONLY, 0111);
	if (fd == -1)
	{
		write(2, OPEN_FILE, ft_strlen(OPEN_FILE));
		return (-1);
	}
	if (read_lines(fd, line, game))
		return (-1);
	close(fd);
	return (0);
}
