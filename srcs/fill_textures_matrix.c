/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_textures_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:59:47 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/09 19:27:37 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static char	fill_textures_path(t_texture *ptr, char *line)
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

char	fill_textures_matrix(char *line, t_vars *vars)
{
	int	i;

	if (*line == 'N')
		i = 0;
	if (*line == 'S')
		i = 1;
	if (*line == 'W')
		i = 2;
	if (*line == 'E')
		i = 3;
	vars->textures[i]->side = *line;
	if (fill_textures_path(vars->textures[i], line))
		return (-1);
	return (0);
}
