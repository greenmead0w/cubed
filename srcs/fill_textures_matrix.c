/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_textures_matrix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:59:47 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 21:38:18 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// static int	calculate_size(char *line)
// {
// 	int	counter;

// 	counter = 2;
// 	line += 2;
// 	while (*line == ' ')
// 		line++;
// 	while (*line != ' ' && *line != '\n')
// 	{
// 		counter++;
// 		line++;
// 	}
// 	return (counter);
// }

// static void	copy_texture(char *dest, char *src)
// {
// 	while (*src != ' ' && *src != '\n')
// 		*dest++ = *src++;
// 	while (*src == ' ')
// 		src++;
// 	while (*src != ' ' && *src != '\n')
// 		*dest++ = *src++;
// 	*dest = '\0';
// }

static char fill_textures_path(t_texture **ptr, int i)
{
	if (i == 0)
		ptr[i]->path = ft_strdup(NORTH_W);
	else if (i == 1)
		ptr[i]->path = ft_strdup(SOUTH_W);
	else if (i == 2)
		ptr[i]->path = ft_strdup(WEST_W);
	else if (i == 3)
		ptr[i]->path = ft_strdup(EAST_W);
	if (!ptr[i]->path)
		return -1;
	return 0;
}

char	fill_textures_matrix(char *line, t_vars *vars)
{
	int	i;
	//int	size;

	if (*line == 'N')
		i = 0;
	if (*line == 'S')
		i = 1;
	if (*line == 'W')
		i = 2;
	if (*line == 'E')
		i = 3;
	vars->textures[i]->side = *line;
	if (fill_textures_path(vars->textures, i))
		return -1;
	return (0);
}
