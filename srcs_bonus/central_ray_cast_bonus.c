/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   central_ray_cast_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:28:53 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/29 21:13:47 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"
#include <stdio.h>
#include <unistd.h>

static void	is_door_close(int x, int y, t_vars *vars, t_ray *ray)
{
	y = 15;
	x = 18;
	if (vars->game_map[y][x] == 'D' && ray->distance < MAX_DIST_TO_OPEN && vars->door_flag)
		vars->game_map[y][x] = 'P';
	else if (vars->game_map[y][x] == 'P' && ray->distance < MAX_DIST_TO_OPEN && vars->door_flag)
		vars->game_map[y][x] = 'D';
	printf("x, y, map %i %i %c\n", y, x, vars->game_map[y][x]); 
	vars->door_flag = 0;
}

void	central_ray_cast(t_ray *ray, t_player *player, t_vars *vars)
{
	t_ray	vert_ray;
	t_ray	horz_ray;
	double	angle;

	printf("(central_ray_casting)\n");
	sleep(1);
	ray->angle = player->rotation_angle;
	angle = standardize_angle(ray->angle);
	vert_ray.angle = angle;
	horz_ray.angle = angle;
	vert_ray.border = 'V';
	horz_ray.border = 'H';
	vars->central_flag = 1;
	vertical_border(&vert_ray, player, vars);
	horizontal_border(&horz_ray, player, vars);
	if (vert_ray.distance < horz_ray.distance)
		*ray = vert_ray;
	else
		*ray = horz_ray;
	vars->central_flag = 0;
	printf("distance %f\n", ray->distance);
	printf("ray_x %f, ray_y %f\n", ray->pos[0], ray->pos[1] - 1);
	is_door_close(ray->pos[0], ray->pos[1] - 1, vars, ray);
}
