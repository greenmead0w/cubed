/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_health_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:11:59 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/27 19:35:28 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static	void	fill_health(t_health *h, t_game *game)
{
	h->width = game->vars->screen_width / 10;
	h->height = h->width / 2;
	h->start_y = game->vars->screen_height / 10;
	h->start_x = game->vars->screen_width - (h->width * 2);
	h->border_c = 0x000000;
	h->life_c = 0x90a955;
	h->damage_c = 0x89818a;
	h->border_width = 4;
	h->end_y = h->start_y + h->height;
	h->end_x = h->start_x + h->width;
}

static	int	is_health_bar_border(int x, int y, t_health h)
{
	if (x < h.start_x + h.border_width || y < h.start_y + h.border_width
		|| x > h.end_x - h.border_width || y > h.end_y - h.border_width)
		return (1);
	return (0);
}

static	void	color_bar(int x, int y, t_health h, t_game *game)
{
	int	bar_size;
	int	x_limit;

	bar_size = (h.width - 2 * h.border_width) * game->player->health / 100;
	x_limit = h.start_x + h.border_width + bar_size;
	if (x <= x_limit)
		put_pixel_to_image(game->conn, x, y, h.life_c);
	else
		put_pixel_to_image(game->conn, x, y, h.damage_c);
}

void	draw_health(t_game *game)
{
	t_health	h;
	int			curr_x;
	int			curr_y;

	fill_health(&h, game);
	curr_y = h.start_y;
	while (curr_y <= h.end_y)
	{
		curr_x = h.start_x;
		while (curr_x <= h.end_x)
		{
			if (is_health_bar_border(curr_x, curr_y, h))
				put_pixel_to_image(game->conn, curr_x, curr_y, h.border_c);
			else
				color_bar(curr_x, curr_y, h, game);
			curr_x++;
		}
		curr_y++;
	}
}

