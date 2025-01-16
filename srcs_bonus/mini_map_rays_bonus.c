/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:23:49 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/10 12:24:08 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
**  0 - initial "x"; 1 - initial "y"; 2 - final "x"; 3 - final "y"
**  Notice cartesian confusion (line, col == y, x)
*/
static	void	get_ray_coordinates(t_ray ray, t_player *player,
	int *line, t_vars *vars)
{
	line[0] = player->play_pos[1] * vars->min_tile;
	line[1] = player->play_pos[0] * vars->min_tile;
	line[2] = line[0] + (cos(ray.angle) * ray.distance * vars->min_tile);
	line[3] = line[1] + (sin(ray.angle) * ray.distance * vars->min_tile);
}

/*
**  the adjacent and opposite variables serve 2 purposes:
**  first they represent differences in x and y coordinates
**  and then are used as unit vectors
**  this is not clean code but capped by max number of variables per function
*/
static	void	draw_ray(int *line, t_conn *conn)
{
	double	adjacent;
	double	opposite;
	int		hypotenuse;
	double	curr_x;
	double	curr_y;

	adjacent = line[2] - line[0];
	opposite = line[3] - line[1];
	hypotenuse = sqrt(pow(adjacent, 2) + pow(opposite, 2));
	adjacent = adjacent / hypotenuse;
	opposite = opposite / hypotenuse;
	curr_x = line[0];
	curr_y = line[1];
	while (hypotenuse)
	{
		put_pixel_to_image(conn, curr_x, curr_y, 0xFF0000);
		curr_x += adjacent;
		curr_y += opposite;
		hypotenuse--;
	}
}

/* for each ray:
    1 - get starting and ending position of ray(x,y) at the pixel level
    2 - calculate adjacent, opposite, hypotenuse
    4 - calculate increment in x and y position of line per pixel
    5 - store data on img, pixel by pixel, up to hypotenuse pixel
    */
void	draw_all_rays(t_game *game)
{
	int	line[4];
	int	i;

	i = 0;
	while (i < game->vars->screen_width)
	{
		get_ray_coordinates(game->rays[i], game->player, line, game->vars);
		draw_ray(line, game->conn);
		i++;
	}
}
