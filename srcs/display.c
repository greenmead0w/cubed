/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:06:48 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/10 12:07:06 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
******************************************************************
*********************DRAW 3D  WALLS******************************
******************************************************************
*/

void	draw_floor(t_game *game)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = combine_rgb(game->color_root, 'F');
	while (x < game->vars->screen_width)
	{
		y = game->vars->screen_height / 2;
		while (y < game->vars->screen_height)
		{
			put_pixel_to_image(game->conn, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = combine_rgb(game->color_root, 'C');
	while (x < game->vars->screen_width)
	{
		y = 0;
		while (y < game->vars->screen_height / 2)
		{
			put_pixel_to_image(game->conn, x, y, color);
			y++;
		}
		x++;
	}
}

/*
**  wall_offset -> if wallHeight > screenHeight only displaying part of wall and 
**  therefore should be displaying part of the texture too. 
**	example: if we display 80% of wall, we need to display 80% of texture. 
**  
**  step -> ratio to determine which texture pixel to sample for each wall pixel
**
**  without the second condition in the while loop program seg-faults
**	when wall_height > screen_height
**
**  tex_line is a double because when it was an int adding step < 1 made it stuck
**  at the same value all the time
*/
static void	mapping_texture_pixels(t_game *game, t_ray ray,
	double wh_pos, int i)
{
	double			step;
	double			wall_offset;
	int				tex_col;
	double			tex_line;
	unsigned int	tex_color;

	wall_offset = 0;
	if (ray.wall_height > game->vars->screen_height)
		wall_offset = (ray.wall_height - game->vars->screen_height) / 2.0;
	step = ray.tex.height / ray.wall_height;
	tex_line = wall_offset * step;
	tex_col = wh_pos * ray.tex.width;
	while (i < ray.wall_height && i < game->vars->screen_height)
	{
		tex_line = fmod(tex_line, ray.tex.height);
		tex_color = get_tex_pixel(ray, tex_col, tex_line);
		put_pixel_to_image(game->conn, ray.x, ray.y + i, tex_color);
		i++;
		tex_line += step;
	}
}

/*
**  for every ray
**  1 - get wall height
**  2 - (x, y) coordinates where the strip will be rendered
**  3 - TEXTURES
**      3.1 - get texture to be rendered
**      3.2 - find where in the wall has the ray impacted
**      3.3 - find appropr. pixel in tex & write to appropr. pxl in screen image
*/
void	draw_ray_cast(t_game *game, int i)
{
	double	wall_hit_pos;

	while (i < game->vars->num_rays)
	{
		adjusted_wall_height(&game->rays[i], game->player, game->vars);
		x_y_wall_rendering_coords(&game->rays[i], game->vars, i);
		game->rays[i].tex = get_ray_texture(game, game->rays[i]);
		wall_hit_pos = find_wall_hit_pos(game->rays[i]);
		mapping_texture_pixels(game, game->rays[i],
			wall_hit_pos, 0);
		i++;
	}
}
