/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_v0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 10:22:33 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

void	get_textures(t_conn *con, t_texture **tex, t_vars *vars)
{
	int	i;

	i = 0;
	printf("%ld\n", strlen(NORTH_W));
	printf("%ld\n", strlen(tex[i]->path));
	while (i < 4)
	{
		printf("[%d]->path is:%s\n", i, tex[i]->path);
		// tex[i]->width = TILE_SIZE;
		// tex[i]->height = TILE_SIZE;
		tex[i]->width = vars->big_tile;
		tex[i]->height = vars->big_tile;
		i++;
	}
	tex[NORTH]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[NORTH]->path, \
		&tex[NORTH]->width, &tex[NORTH]->height);
	tex[SOUTH]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[SOUTH]->path, \
		&tex[SOUTH]->width, &tex[SOUTH]->height);
	tex[EAST]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[EAST]->path, \
		&tex[EAST]->width, &tex[EAST]->height);
	tex[WEST]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[WEST]->path, \
		&tex[WEST]->width, &tex[WEST]->height);
	i = 0;
	if (!tex[NORTH]->img.ptr)
	{
		printf("null - 1\n");
		if (!tex[SOUTH]->img.ptr)
		{
			printf("null - 2\n");
			if (!tex[EAST]->img.ptr)
			{
				printf("null - 3\n");
			}
		}
	}
	while (i < 4)
	{
		tex[i]->img.addr = mlx_get_data_addr(tex[i]->img.ptr, \
			&tex[i]->img.bpp, &tex[i]->img.line_length, \
			&tex[i]->img.endian);
		i++;
	}
}
