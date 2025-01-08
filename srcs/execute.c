/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/08 20:55:14 by dpinedo-         ###   ########.fr       */
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
		free_all_game(game);
		return ((void *)1);
	}
	game->player->turn_direction = 0;
	game->player->walk_direction = '0';
	game->player->rotation_speed = 2 *(M_PI / 180);
	game->player->speed = 10.0 / 64;
	initial_player_data(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->player);
	game->player->field_of_view = 60 * (M_PI / 180);
	game->player->dist_to_plane = (game->vars->screen_width / 2)
		/ (tan(game->player->field_of_view / 2));
	game->player->display_size = MINI_TILE / 2.0;
	printf("turn_direction is: %c\n", game->player->turn_direction);
	printf("walk_direction is: %c\n", game->player->walk_direction);
	printf("rotation_angle is: %f\n", game->player->rotation_angle);
	printf("rotation_speed is: %f\n", game->player->rotation_speed);
	printf("speed is: %f\n", game->player->speed);
	printf("pos_line is: %f\n", game->player->play_pos[0]);
	printf("pos_col is: %f\n", game->player->play_pos[1]);
	printf("distance to projection plane is: %f\n", game->player->dist_to_plane);
	printf("----------------\n");
	printf("SCREEN_WIDTH is: %d\n", game->vars->screen_width);
	printf("SCREEN_HEIGHT is: %d\n", game->vars->screen_height);
	printf("%d\n", MINI_TILE);
	printf("rows(y) is: %d\n", game->vars->map_rows);
	printf("cols(y) is: %d\n", game->vars->map_cols);
	return ((void *)0);
}

static int	init_game(t_game *game)
{
	get_textures(game->conn, game->vars->textures);
	if (init_player(game))
		return (-1);
	game->vars->num_rays = game->vars->screen_width / RAY_WIDTH;
	game->rays = malloc(game->vars->num_rays * sizeof(t_ray));
	if (!game->rays)
	{
		free_all_game(game);
		return (1);
	}
	ft_bzero(game->rays, sizeof(t_ray));
	game->update = 1;
	printf("num_rays is: %d\n", game->vars->num_rays);
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
		g->update = 0;
	}
	draw_ceiling(g);
	draw_floor(g);
	draw_ray_cast(g, 0);
	draw_2d_map(g);
	draw_all_rays(g);
	draw_player(g->conn, g->player);
	mlx_put_image_to_window(g->conn->mlx, g->conn->win,
		g->conn->image.ptr, 0, 0);
	mlx_destroy_image(g->conn->mlx, g->conn->image.ptr);
	return (0);
}

char	execute(t_game *game)
{
	if (create_connection(game) || init_game(game))
		return (-1);
	mlx_hook(game->conn->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->conn->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game);
	mlx_loop_hook(game->conn->mlx, render_game, game);
	mlx_loop(game->conn->mlx);
	return (0);
}
