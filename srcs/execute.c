/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/15 21:05:58 by dpinedo-         ###   ########.fr       */
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
	game->player->rotation_speed = 2 *(M_PI / 180);
	game->player->speed = 10.0 / 64;
	initial_player_data(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->player);
	game->player->field_of_view = 60 * (M_PI / 180);
	game->player->dist_to_plane = (game->vars->screen_width / 2)
		/ (tan(game->player->field_of_view / 2));
	game->player->display_size = game->vars->min_tile / 2.0;
	return ((void *) 0);
}

static int	init_game(t_game *game)
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

/*
** called many times per second (imitating frames per second) to:
** 1 - create an image
** 2 - update game data (if player pos has changed / keyPressed)
** 3 - fill image with updated data
** 4 - dump image data onto window
** 5 - clear image

** NOT CHECKING IF MLX_NEW_IMAGE() OR MLX_GET_DATA_ADDR ERROR
*/
static int	render_game(void *game)
{
	t_game	*g;

	g = (t_game *)game;
	g->conn->image.ptr = mlx_new_image(g->conn->mlx,
			g->vars->screen_width, g->vars->screen_height);
	g->conn->image.addr = mlx_get_data_addr(g->conn->image.ptr,
			&g->conn->image.bpp, &g->conn->image.line_length,
			&g->conn->image.endian);
	if (g->update)
	{
		update(g);
		if (!SPEED)
			g->update = 0;
	}
	draw_ceiling(g);
	draw_floor(g);
	draw_ray_cast(g, 0);
	draw_2d_map(g);
	draw_all_rays(g);
	draw_player(g->conn, g->player, g->vars);
	mlx_put_image_to_window(g->conn->mlx, g->conn->win,
		g->conn->image.ptr, 0, 0);
	mlx_destroy_image(g->conn->mlx, g->conn->image.ptr);
	return (0);
}

char	execute(t_game *game)
{
	if (create_connection(game) || init_game(game))
	{
		free_all_game(game);
		return (-1);
	}
	mlx_hook(game->conn->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->conn->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game);
	mlx_loop_hook(game->conn->mlx, render_game, game);
	mlx_loop(game->conn->mlx);
	return (0);
}
