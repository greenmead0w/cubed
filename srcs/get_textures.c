/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/26 08:31:52 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_textures(t_conn *con, t_texture **textures)
{
	int i;

	i = 0;
	while( i < 4)
	{
		textures[i]->width = TILE_SIZE;
		textures[i]->height = TILE_SIZE;
		i++;
	}
	textures[NORTH]->img.ptr = XPM_TO_IMAGE(con->mlx, NORTH_W,
		 &textures[NORTH]->width, &textures[NORTH]->height);
	textures[SOUTH]->img.ptr = XPM_TO_IMAGE(con->mlx, SOUTH_W, 
		&textures[SOUTH]->width, &textures[SOUTH]->height);
	textures[EAST]->img.ptr = XPM_TO_IMAGE(con->mlx, EAST_W, 
		&textures[EAST]->width, &textures[EAST]->height);
	textures[WEST]->img.ptr = XPM_TO_IMAGE(con->mlx, WEST_W, 
		&textures[WEST]->width, &textures[WEST]->height);
	i = 0;
	while (i < 4)
	{
		textures[i]->img.addr = mlx_get_data_addr(textures[i]->img.ptr, 
			&textures[i]->img.bpp, &textures[i]->img.line_length, &textures[i]->img.endian);
		i++;
	}
}
