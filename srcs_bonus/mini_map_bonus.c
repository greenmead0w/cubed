/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:24:21 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/28 19:36:26 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static void	fill_player_rect(t_conn *conn, int center_x, int center_y,
	int size)
{
	int	x_start;
	int	x_end;
	int	y_start;
	int	y_end;
	int	current_x;

	x_start = center_x - (size / 2);
	x_end = center_x + (size / 2);
	y_start = center_y - (size / 2);
	y_end = center_y + (size / 2);
	while (y_start <= y_end)
	{
		current_x = x_start;
		while (current_x <= x_end)
		{
			put_pixel_to_image(conn, current_x, y_start, 0xFF0000);
			current_x++;
		}
		y_start++;
	}
}

/*
**  Multiplying by min_tile to find the scaled down player position
**  Player is half the size of a mini map tile
*/
void	draw_player(t_conn *conn, t_player *player, t_vars *vars)
{
	int		center_x;
	int		center_y;
	double	size;

	center_x = player->play_pos[1] * vars->min_tile;
	center_y = player->play_pos[0] * vars->min_tile;
	size = vars->min_tile / 2;
	fill_player_rect(conn, center_x, center_y, size);
}

static void	draw_row(t_draw_2d *p, t_game *game)
{
	int	remaining;

	p->curr_x = p->start_x;
	remaining = game->vars->min_tile;
	while (remaining)
	{
		if (is_border_map(p, game->vars))
			put_pixel_to_image(game->conn, p->curr_x, p->curr_y, 0xFFA500);
		else if (p->value == '1' || p->value == ' ')
			put_pixel_to_image(game->conn, p->curr_x, p->curr_y, 0x000000);
		else if (p->value == 'D')
			put_pixel_to_image(game->conn, p->curr_x, p->curr_y, 0x142157);
		else
			put_pixel_to_image(game->conn, p->curr_x, p->curr_y, 0xFFFFFF);
		p->curr_x++;
		remaining--;
	}
}

static void	draw_tile(char value, t_game *game, int row, int col)
{
	t_draw_2d	p;
	int			remaining;

	p.start_y = row * game->vars->min_tile;
	p.start_x = col * game->vars->min_tile;
	p.curr_y = p.start_y;
	p.value = value;
	remaining = game->vars->min_tile;
	while (remaining)
	{
		draw_row(&p, game);
		p.curr_y++;
		remaining--;
	}
}

void	draw_2d_map(t_game *game)
{
	char	**map;
	int		row;
	int		col;

	map = game->vars->game_map;
	row = 0;
	while (row < game->vars->map_rows)
	{
		col = 0;
		while (col < game->vars->map_cols)
		{
			draw_tile(map[row][col], game, row, col);
			col++;
		}
		row++;
	}
}
