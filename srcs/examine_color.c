/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   examine_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:18:00 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/22 18:56:41 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static char	revise_digit(char **line)
{
	int	digit_number;

	digit_number = count_digits(line);
	if (digit_number < 1 || digit_number > 3)
	{
		write(2, COLOR, ft_strlen(COLOR));
		return (-1);
	}
	return (0);
}

static char	check_floor_ceiling(char *line)
{
	int	counter;

	counter = 0;
	while (*line == ' ')
		line++;
	while (*line != '\n' && *line)
	{
		if (revise_digit(&line))
			return (-1);
		if (*line == ',')
			line++;
		counter++;
	}
	if (counter != 3)
	{
		write(2, COLOR, ft_strlen(COLOR));
		return (-1);
	}
	return (0);
}

char    examine_color(char *line, t_track_items track_elems)
{
	int	i;
	char	color_flag;

	i = 0;
	color_flag = 0;
	while (i < COLORS_NUM)
	{
		if (*line == SET[i] && !track_elems->colors_ok[i])
		{
			if (check_floor_ceiling(line + 1))
				return (-1);
			track_elems->colors_ok[i] = 1;
			track_elems->item_counter++;
			color_flag = 1;
			i = COLORS_NUM;
		}
		i++;
	}
	if (color_flag = 0)
	{
		write(2, COLOR_X_2, ft_strlen(COLOR_X_2));
		return (-1);
	}
}
