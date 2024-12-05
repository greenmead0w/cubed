/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:16:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/26 21:51:01 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <fcntl.h>

/*
** dudas:
** 1- el fichero puede tener caracteres no alfanuméricos ("-" o "_" o "+")?
** 2 - la función valida la sintaxis, pero no si el fichero existe
**		por ejemplo daría como bueno a "./no./.existe./"
** alternativa por si no funciona: hacer un open(line) y si da error retornar -1
*/
// static char	check_texture(char *line)
// {
// 	while (*line == ' ')
// 		line++;
// 	if (*line != '.' || *(line + 1) != '/' || !ft_isalnum(*(line + 2)))
// 	{
// 		write(2, PATH, ft_strlen(PATH));
// 		return (-1);
// 	}
// 	while (*line != ' ' && *line != '\n' && *line)
// 		line++;
// 	while (*line == ' ')
// 		line++;
// 	if (*line != '\n')
// 	{
// 		write(2, PATH, ft_strlen(PATH));
// 		return (-1);
// 	}
// 	return (0);
// }


//alternativa a check_texture:
static char	alternative_check_texture(char *line)
{
	int		fd;
	char	*start;
	char	temp;

	while (*line == ' ')
		line++;
	start = line;
	while (*line != '\n' && *line)
		line++;
	temp = *line; //añadir caracter nulo temporalmente, para que el path termine ahí
	*line = '\0';
	fd = open(start, O_RDONLY);
	*line = temp; //restablecer ' ' ó '\n'
	if (fd == -1 || texture_extension(line, start, fd))
	{
		write(2, PATH, ft_strlen(PATH));
		return (-1);
	}
	close(fd);
	return (0);
}

static char	examine_texture(char *line, t_track_items *track_elems)
{
	int		i;
	char	texture_flag;

	i = 0;
	texture_flag = 0;
	while (i < TEXTURES_NUM)
	{
		if (cmp_to_one_text(line, i) && !track_elems->textures_ok[i])
		{
			if (alternative_check_texture(line + 2)) //modificado
				return (-1);
			track_elems->textures_ok[i] = 1;
			track_elems->item_counter++;
			texture_flag = 1;
			i = TEXTURES_NUM;
		}
		i++;
	}
	if (texture_flag == 0)
	{
		write(2, TEXTURES_X_2, ft_strlen(TEXTURES_X_2));
		return (-1);
	}
	return (0);
}

/*
**	primera lectura del .cub. 
**	se validan colores, texturas y se cuentan las lineas del mapa
**
**	daba errores. he modificado:
**	inicializar result = 0 (antes -1 daba error cuando se leía la primera linea del mapa y no se actualizaba result)
**	devuelve directamente result
*/
char	examine_line(char *line, t_game *game, t_track_items *track_elems)
{
	char	result;

	result = -1;
	if (!line)
		return (-1);
	if (*line == '\n' && track_elems->map_flag != 1)
		return (0);
	while (*line == ' ')
		line++;
	if (*line == 'F' || (*line == 'C' && track_elems->map_flag != 1))
		result = examine_color(line, track_elems);
	else if (!compare_to_all_textures(line) && track_elems->map_flag != 1)
		result = examine_texture(line, track_elems);
	else if (*line == '1' && track_elems->item_counter == 6)
	{
		if (track_elems->map_flag == 0)
			track_elems->map_flag = 1;
		game->map_rows_counter++;
		result = 0;
	}
	else
		// write(2, WRONG_FILE, ft_strlen(WRONG_FILE));
	{
		if (track_elems->map_flag != 1)
			write(2, WRONG_FILE, ft_strlen(WRONG_FILE));
		else
			write(2, WALLS, ft_strlen(WALLS));
	}
	return (result);
}
