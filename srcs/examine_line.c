/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:16:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/20 21:21:23 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static char	check_texture(char *line)
{
	while (*line == ' ')
		line++;
	if (*line != '.' || *(line + 1) != '/' || !ft_isalnum(*(line + 2)))
	{
		write(2, PATH, ft_strlen(PATH));
		return (-1);
	}
	while (*line != ' ' && *line != '\n' && *line)
		line++;
	while (*line == ' ')
		line++;
	if (*line != '\n')
	{
		write(2, PATH, ft_strlen(PATH));
		return (-1);
	}
	return (0);
}

static char    examine_texture(char *line, t_track_elems)
{
	int	i;
	char	texture_flag;

	i = 0;
	color_flag = 0;
	while (i < TEXTURES_NUM)
	{
		if (cmp_to_one_text(line, i) && !track_elems->textures_ok[i])
		{
			if (check_texture(line + 2))
				return (-1);
			track_elems->colors_textures[i] = 1;
			track_elems->item_counter++;
			texture_flag = 1;
			i = TEXTURES_NUM;
		}
		i++;
	}
	if (texture_flag = 0)
	{
		write(2, TEXTURES_X_2, ft_strlen(TEXTURES_X_2));
		return (-1);
	}
}

char	examine_line(char *line, t_game *game, t_track_items *track elems)
{
	char	result;

	result = -1;
	if (!line)
		return (-1);
	if (*line == '\n' && track_elems->map_flag != 1)
		return (0);
	while (*line == ' ')
		line++;
	if (*line == 'F' || *line == 'C' && track_elems->map_flag != 1)
		result = examine_color(line, track_elems);
	else if (!compare_to_all_textures(line) && track_elems->map_flag != 1)
		result = examine_texture(line, track_elems);
	else if (*line == '1' && items_counter == 6)
	{
		if (track_elems->map_flag == 0)
			track_elems->map_flag == 1;
		game->map_rows_counter++;
	}
	else
		write(2, WRONG_FILE, ft_strlen(WRONG_FILE));
	if (result)
		return (-1);
	return (0);
}
