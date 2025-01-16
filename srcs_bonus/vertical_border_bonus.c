/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_border.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:55:43 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:39:24 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
**  solving for the opposite
**  find x,y coordinates of point a, which is first vertical border the ray hits
**  stores the rays distance to the border
*/
static void	vert_find_point_a(t_ray *ray, t_player *player, char flag)
{
	double	x;
	double	y;
	double	adjacent;
	double	opposite;

	if (flag == 'r')
		x = (int)(player->play_pos[1] +1);
	else
		x = (int)player->play_pos[1];
	adjacent = x - player->play_pos[1];
	opposite = tan(ray->angle) * adjacent;
	y = player->play_pos[0] + opposite;
	ray->pos[0] = x;
	ray->pos[1] = y;
	ray->distance = sqrt(pow(adjacent, 2) + pow(opposite, 2));
}

/* delta_x; //adjacent tile_size increment in borders
** delta_y; //opposite
*/

static void	right_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	double	tile_increment;

	delta_x = 1;
	vert_find_point_a(ray, player, 'r');
	if (ray_is_wall(ray->pos[0], ray->pos[1], vars, ray))
		return ;
	delta_y = tan(ray->angle) * delta_x;
	tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	while (!ray_is_wall(ray->pos[0], ray->pos[1], vars, ray))
	{
		ray->pos[0] += delta_x;
		ray->pos[1] += delta_y;
		ray->distance += tile_increment;
	}
}

/*
**  different from a righ_facing_ray in :
**  1 - how to find point a
**  2 - adjacent is negative
**  3 - the border is part of which tile?
**  delta_x; //adjacent TILE_SIZE decrease in vertical borders
**  delta_y; //opposite
*/
static void	left_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	double	tile_increment;

	delta_x = -1;
	vert_find_point_a(ray, player, 'l');
	if (ray_is_wall(ray->pos[0] -1, ray->pos[1], vars, ray))
		return ;
	delta_y = tan(ray->angle) * delta_x;
	tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	while (!ray_is_wall(ray->pos[0] - 1, ray->pos[1], vars, ray))
	{
		ray->pos[0] += delta_x;
		ray->pos[1] += delta_y;
		ray->distance += tile_increment;
	}
}

/*
** INT_MAX to prevent infinite loop if ray doesn't hit any vertical border,
**  when angle is either 90 or 270 degrees
** can we run into rounding problems due to floating imprecision??
*/
void	vertical_border(t_ray *ray, t_player *player, t_vars *vars)
{
	if (ray->angle == 90 * M_PI / 180 || ray->angle == 270 * M_PI / 180)
	{
		ray->distance = INT_MAX;
		return ;
	}
	if (ray->angle > 270 * M_PI / 180 || ray->angle < 90 * M_PI / 180)
		right_facing_ray(ray, player, vars);
	else
		left_facing_ray(ray, player, vars);
}
