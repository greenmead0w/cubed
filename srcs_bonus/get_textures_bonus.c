/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 21:41:18 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/29 19:47:30 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	set_animate_images_path(t_texture **type, int n, enum e_mode mode)
{
	int	i;
	char	*animate_path;

	i = 0;
	if (mode == animate_empty_stadium)
		animate_path = "textures/empty_stadium.xpm";
	else if (mode == animate_spectators_up)
		animate_path = "textures/stadium_cheering.xpm";
	else if (mode == door)
	{
		type[0]->path = "textures/door.xpm";
		type[0]->side = 'D';
		return ;
	}
	while (i < n)
	{
		type[i]->path = animate_path;
		type[i]->side = SET_2[i];
		i++;
	}
}

static char	get_xml_images_from_xpm(t_conn *con, t_texture **type, t_vars *vars, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		type[i]->width = vars->big_tile;
		type[i]->height = vars->big_tile;
		type[i]->img.ptr = XPM_TO_IMAGE(con->mlx, type[i]->path, \
			&type[i]->width, &type[i]->height);
		if (!type[i]->img.ptr)
		{
			write(2, TEXT_LOAD, ft_strlen(TEXT_LOAD));
			return (-1);
		}
		type[i]->img.addr = mlx_get_data_addr(type[i]->img.ptr, \
			&type[i]->img.bpp, &type[i]->img.line_length, \
			&type[i]->img.endian);
		if (!type[i]->img.addr)
		{
			write(2, TEXT_LOAD, ft_strlen(TEXT_LOAD));
			return (-1);
		}
		i++;
	}
	return (0);
}

char	get_textures(t_conn *con, t_vars *vars)
{
	set_animate_images_path(vars->animate_empty, SIDES, animate_empty_stadium);
	set_animate_images_path(vars->animate_cheer, SIDES, animate_spectators_up);
	set_animate_images_path(vars->door_texture, 1, door);
	if (get_xml_images_from_xpm(con, vars->walls, vars, SIDES))
		return (-1);
	if (get_xml_images_from_xpm(con, vars->animate_empty, vars, SIDES))
		return (-1);
	if (get_xml_images_from_xpm(con, vars->animate_cheer, vars, SIDES))
		return (-1);
	if (get_xml_images_from_xpm(con, vars->door_texture, vars, 1))
		return (-1);
	return (0);
}
