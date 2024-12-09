/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:54:08 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 21:43:16 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <fcntl.h>

/*
**	parsea colores en lista enlazada, texturas en una matriz y 
**	copia el mapa (no validado todavía) en una matriz
*/
static char	parse_items(char *line, t_game *game)
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
	{
		result = fill_colors_list(run, game);
	}
	else if (!compare_to_all_textures(run))
		result = fill_textures_matrix(run, game->vars);
	else if (*run == '1')
		result = fill_map(game->vars, line);
	else
		write(2, WRONG_FILE, ft_strlen(WRONG_FILE));
	if (result)
		return (-1);
	return (0);
}

/*
**	segunda lectura del .cub, sirve para:
**	fill la lista enlazada de colores
**	fill la matriz de texturas
**	parsear primera versión del mapa
*/
static char	read_lines(int fd, char *line, t_game *game)
{
	while (line)
	{
		line = get_next_line(fd);
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
	game->vars->map = malloc(sizeof(void *) * (game->vars->map_rows + 1));
	if (!game->vars->map)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	game->vars->map[game->vars->map_rows] = (void *) 0;
	return (0);
}

char	parse(char *file, t_game *game)
{
	char	*line;
	int		fd;

	if (initialize_map_matrix(game))
		return (-1);
	line = (char *) 1;
	fd = open(file, O_RDONLY, 0111); //no hace falta tercer argumento creo
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
