/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_border.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 22:01:58 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:21:26 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
**	solving for the adjacent
**	opposite = y - player->play_pos[0] --> opposite is negative when upwards
**	adjacent = opposite / tan(ray->angle) -->if tan(ray->angle) is almost 0?
*/
static void	horz_find_point_a(t_ray *ray, t_player *player, char flag)
{
	double	x;
	double	y;
	double	adjacent;
	double	opposite;

	if (flag == 'u')
		y = (int)player->play_pos[0];
	else
		y = (int)(player->play_pos[0] +1);
	opposite = y - player->play_pos[0];
	adjacent = opposite / tan(ray->angle);
	x = player->play_pos[1] + adjacent;
	ray->pos[0] = x;
	ray->pos[1] = y;
	ray->distance = sqrt(pow(adjacent, 2) + pow(opposite, 2));
}

/*  delta_x; //adjacent
** delta_y; //opposite, tile_size decrease in horz borders
*/
static void	upwards_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	double	tile_increment;

	delta_y = -1;
	horz_find_point_a(ray, player, 'u');
	if (ray_is_wall_bonus(ray->pos[0], ray->pos[1] - 1, vars, ray))
		return ;
	delta_x = delta_y / tan(ray->angle);
	tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	while (!ray_is_wall_bonus(ray->pos[0], ray->pos[1] - 1, vars, ray))
	{
		ray->pos[0] += delta_x;
		ray->pos[1] += delta_y;
		ray->distance += tile_increment;
	}
}

/*  delta_x; //adjacent
** delta_y; //opposite TILE_SIZE increase in horz borders
*/

static void	downwards_facing_ray(t_ray *ray, t_player *player, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	double	tile_increment;

	delta_y = 1;
	horz_find_point_a(ray, player, 'd');
	if (ray_is_wall_bonus(ray->pos[0], ray->pos[1], vars, ray))
		return ;
	delta_x = delta_y / tan(ray->angle);
	tile_increment = sqrt(pow(delta_x, 2) + pow(delta_y, 2));
	while (!ray_is_wall_bonus(ray->pos[0], ray->pos[1], vars, ray))
	{
		ray->pos[0] += delta_x;
		ray->pos[1] += delta_y;
		ray->distance += tile_increment;
	}
}

/*
** EPSILON is a macro that acts as aproximation to 0, because
** in angles of 0, 180, 360 degrees the tangent is 0, or very close to it
** and the adjacent will result in very very big numbers
*/
void	horizontal_border(t_ray *ray, t_player *player, t_vars *vars)
{
	if (ray->angle < EPSILON || fmod(ray->angle, M_PI) < EPSILON)
	{
		ray->distance = INT_MAX;
		return ;
	}
	if (ray->angle > M_PI)
		upwards_facing_ray(ray, player, vars);
	else
		downwards_facing_ray(ray, player, vars);
}
