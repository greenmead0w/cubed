/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:31:31 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/10 12:37:50 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
**	if (ray->angle > 0 && ray->angle < M_PI)--> ray going bottom (graphically)
**	if ((ray->angle > 3 * M_PI / 2 && ray->angle <= 2 * M_PI)
		|| (ray->angle >= 0 && ray->angle < M_PI / 2)) //ray going east
*/
static char	wall_side_hit(int x, int y, t_vars *vars, t_ray *ray)
{
	if (x == 0)
		return ('E');
	if (y == 0)
		return ('S');
	if (x == vars->map_cols)
		return ('W');
	if (y == vars->map_rows -1)
		return ('N');
	if (ray->border == 'H')
	{
		if (ray->angle > 0 && ray->angle < M_PI)
			return ('N');
		else if (ray->angle > M_PI && ray->angle < 2 * M_PI)
			return ('S');
	}
	if (ray->border == 'V')
	{
		if ((ray->angle > 3 * M_PI / 2 && ray->angle <= 2 * M_PI)
			|| (ray->angle >= 0 && ray->angle < M_PI / 2))
			return ('W');
		else if (ray->angle > M_PI / 2 && ray->angle < 3 * M_PI / 2)
			return ('E');
	}
	return (0);
}

/*
**	function called in update_player_position() and when casting rays
**	in the first case ray is passed as null, in the second one we prevent the ray
**	from being chosen by setting its value high
**	if (y == vars->map_rows) --> last row of char ** is null, 
**	if doing game_map[last_row] then seg fault
*/
int	ray_is_wall(int x, int y, t_vars *vars, t_ray *ray)
{
	if (x > vars->map_cols || x < 0 || y < 0 || y > vars->map_rows)
	{
		ray->distance = INT_MAX;
		return (1);
	}
	if (y == vars->map_rows)
	{
		ray->hit_side = 'N';
		return (1);
	}
	if (vars->game_map[y][x] == '1' )
	{
		ray->hit_side = wall_side_hit(x, y, vars, ray);
		return (1);
	}
	else
		return (0);
}

int	pos_is_wall(double x, double y, t_vars *vars)
{
	int	ix;
	int	iy;

	ix = (int)x;
	iy = (int)y;
	if (ix > vars->map_cols || ix < 0 || iy < 0 || iy > vars->map_rows)
		return (1);
	if (vars->game_map[iy][ix] == '1' )
		return (1);
	else
		return (0);
}

/*
**	Without this function only checking the center of the rectangle,
**	not the edges or sides, and in many cases the center is not in the wall,
**	but the edges / sides are.
**	
**	collision_margin explanation:
**	1 - x and y params are grid indexes, player->display_size is 8 pixels,
**	so dividing by TILE_SIZE makes everything comparable in grid units
**	2 - Dividing by 2 because it's a square and we get the corners / sides 
**	of the square
**		
**	Important note: MINI_TILE scale is only used for displaying purposes,
**	the wall collision detection needs to work at the full TILE_SIZE scale,
**	that's why we harmonize grid values
**	by dividing by TILE_SIZE
**
*/
int	is_collision(double x, double y, t_player *player, t_vars *vars)
{
	double	left;
	double	right;
	double	top;
	double	base;
	double	collision_margin;

	collision_margin = (player->display_size / vars->big_tile) / 2;
	left = x - collision_margin;
	right = x + collision_margin;
	top = y - collision_margin;
	base = y + collision_margin;
	if (pos_is_wall(left, top, vars) || pos_is_wall(left, base, vars)
		|| pos_is_wall(right, top, vars) || pos_is_wall(right, base, vars)
		|| pos_is_wall(left, y, vars) || pos_is_wall(right, y, vars)
		|| pos_is_wall(x, top, vars) || pos_is_wall(x, base, vars))
		return (1);
	return (0);
}
