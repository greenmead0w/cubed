/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 19:14:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/20 19:15:27 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
**	game->player->speed = 10.0/64; --> pixels per key_press
*/
static void	*init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return ((void *) 1);
	}
	game->player->turn_direction = 0;
	game->player->walk_direction = 0;
	game->player->rotation_speed = 8 * (M_PI / 180);
	game->player->speed = 10.0 / 64;
	initial_player_data(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->player);
	game->player->field_of_view = 60 * (M_PI / 180);
	game->player->dist_to_plane = (game->vars->screen_width / 2)
		/ (tan(game->player->field_of_view / 2));
	game->player->display_size = game->vars->min_tile / 2.0;
	return ((void *) 0);
}

int	init_game(t_game *game)
{
	if (get_textures(game->conn, game->vars->textures, game->vars))
		return (-1);
	if (init_player(game))
		return (-1);
	game->vars->num_rays = game->vars->screen_width / RAY_WIDTH;
	game->rays = malloc(game->vars->num_rays * sizeof(t_ray));
	if (!game->rays)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	ft_bzero(game->rays, sizeof(t_ray));
	game->update = 1;
	return (0);
}
