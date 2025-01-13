/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/13 12:11:29 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <string.h>

char	get_textures(t_conn *con, t_texture **tex, t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tex[i]->width = vars->big_tile;
		tex[i]->height = vars->big_tile;
		tex[i]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[i]->path, \
			&tex[i]->width, &tex[i]->height);
		tex[i]->img.addr = mlx_get_data_addr(tex[i]->img.ptr, \
			&tex[i]->img.bpp, &tex[i]->img.line_length, \
			&tex[i]->img.endian);
		if (!tex[i]->img.ptr || !tex[i]->img.addr)
			return (-1);
		i++;
	}
	return (0);
}
