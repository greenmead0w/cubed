/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:43:39 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/23 20:13:08 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

t_texture	get_ray_texture(t_game *game, t_ray ray)
{
	t_texture	*texture;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (ray.hit_side == SET_2[i])
			texture = game->vars->textures[i];
		i++;
	}
	return (*texture);
}

/*
**  multiplying ray->distance by TILE_SIZE to go from grid-values distance
**  to pixels
**
**  wall size is calculated via triangle similarity theorem
*/
void	adjusted_wall_height(t_ray *ray, t_player *player, t_vars *vars)
{
	double	fisheye;
	double	adjusted_distance;
	double	wall_size;

	fisheye = cos(ray->angle - player->rotation_angle);
	adjusted_distance = ray->distance * fisheye * vars->big_tile;
	wall_size = (vars->big_tile / adjusted_distance) * player->dist_to_plane;
	ray->wall_height = wall_size;
}

/*
**  the if condition prevents from drawing out of screen bounds
**  it means that when wall_height > screen_height then start drawing
**  at top y coordinate
*/
void	x_y_wall_rendering_coords(t_ray *ray, t_vars *vars, int i)
{
	int	x;
	int	y;

	x = i * RAY_WIDTH;
	y = (vars->screen_height - ray->wall_height) / 2;
	if (y < 0)
		y = 0;
	ray->x = x;
	ray->y = y;
}

double	find_wall_hit_pos(t_ray ray)
{
	double	wall_hit_pos;

	if (ray.border == 'H')
		wall_hit_pos = ray.pos[0] - floor(ray.pos[0]);
	else
		wall_hit_pos = ray.pos[1] - floor(ray.pos[1]);
	return (wall_hit_pos);
}

/*
**  finds the byte at x,y position on the texture image
**  casting to (unsigned int *) makes it return next 4 bytes (1 pixel)
*/
unsigned int	get_tex_pixel(t_ray ray, int x, int y)
{
	char			*pixel;
	unsigned int	color;

	pixel = ray.tex.img.addr + (y * ray.tex.img.line_length
			+ x * (ray.tex.img.bpp / 8));
	color = *(unsigned int *)pixel;
	return (color);
}
