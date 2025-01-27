/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_walls_matrix_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:59:47 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/23 21:51:11 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static char	fill_walls_path(t_texture *ptr, char *line)
{
	char	**split;
	int		len;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (-1);
	len = ft_strlen(split[1]);
	ptr->path = malloc(len);
	if (!ptr->path)
	{
		free_double_pointer((void **)split);
		return (-1);
	}
	i = 0;
	while (split[1][i] && split[1][i] != '\n')
	{
		ptr->path[i] = split[1][i];
		i++;
	}
	ptr->path[i] = '\0';
	free_double_pointer((void **)split);
	return (0);
}

char	fill_walls_matrix(char *line, t_vars *vars)
{
	int	i;

	if (*line == 'N')
		i = 0;
	if (*line == 'S')
		i = 1;
	if (*line == 'E')
		i = 2;
	if (*line == 'W')
		i = 3;
	vars->walls[i]->side = *line;
	if (fill_walls_path(vars->walls[i], line))
		return (-1);
	return (0);
}
