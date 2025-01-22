/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/13 19:40:01 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

char	get_wall_textures_bonus(t_conn *con, t_texture **tex, t_vars *vars)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		tex[i]->width = vars->big_tile;
		tex[i]->height = vars->big_tile;
		tex[i]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[i]->path, \
			&tex[i]->width, &tex[i]->height);
		tex[i]->img.ptr = XPM_TO_IMAGE(con->mlx, tex[i]->path, \
			&tex[i]->width, &tex[i]->height);			
		tex[i]->img.addr = mlx_get_data_addr(tex[i]->img.ptr, \
			&tex[i]->img.bpp, &tex[i]->img.line_length, \
			&tex[i]->img.endian);
		if (!tex[i]->img.ptr || !tex[i]->img.addr)
		{
			write(2, TEXT_LOAD, ft_strlen(TEXT_LOAD));
			return (-1);
		}
		i++;
	}
	return (0);
}

static	char	get_door_textures_bonus(t_conn *con, t_texture *tex, t_vars *vars, char *path)
{
	tex->width = vars->big_tile;
	tex->height = vars->big_tile;
	tex->path = path;
	tex->img.ptr = XPM_TO_IMAGE(con->mlx, path, \
			&tex->width, &tex->height);
	tex->img.addr = mlx_get_data_addr(tex->img.ptr, \
		&tex->img.bpp, &tex->img.line_length, \
		&tex->img.endian);
	if (!tex->img.ptr || !tex->img.addr)
	{
		write(2, TEXT_LOAD, ft_strlen(TEXT_LOAD));
		return (-1);
	}
	return (0);
}

char	get_doors_textures(t_game *g)
{
	int i;

	i = 0;
	while (i < g->vars->door_count)
	{
		if (get_door_textures_bonus(g->conn, &g->vars->door[i].tex_close, g->vars, DOOR_CLOSE))
			return (-1);
		if (get_door_textures_bonus(g->conn, &g->vars->door[i].tex_open, g->vars, DOOR_OPEN))
			return (-1);
		i++;
	}
	return (0);
}