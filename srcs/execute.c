/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/27 12:36:49 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	*open_connection(t_conn *conn, t_vars *vars)
{
	
	conn->mlx = mlx_init();
	if (!conn->mlx)
		return ((void *) 0);
	vars->screen_width = vars->map_cols * TILE_SIZE;
	vars->screen_height = vars->map_rows * TILE_SIZE;
	conn->win = mlx_new_window(conn->mlx, vars->screen_width, vars->screen_height, "cubed");
	if (!conn->win)
	{
		free(conn->mlx);
		conn->mlx = 0;
		return ((void *) 0);
	}
	return ((void *) 1);
}

static void	*create_connection(t_game *game)
{
	game->conn = malloc(sizeof(t_conn));
	if (!game->conn)
	{
		free_all_game(game);
		return ((void *)0);
	}
	ft_bzero(game->conn, sizeof(t_conn));
	if (!open_connection(game->conn, game->vars))
	{
		free_all_game(game);
		return ((void *)0);
	}
	return ((void *)1);

}

static void	*init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	if (!game->player)
	{
		free_all_game(game);
		return ((void *)0);
	}
	game->player->turn_direction = 0;
	game->player->walk_direction = '0';
	game->player->rotation_angle = M_PI / 2; //90 degrees in radians
	game->player->rotation_speed = 2 *(M_PI / 180); //equivalent of 2 degrees in radians
	game->player->speed = 10.0/64; //pixels per key_press
	initial_player_data(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->player);
	game->player->field_of_view = 60 * (M_PI/180);
	game->player->dist_to_plane = (game->vars->screen_width / 2) / (tan(game->player->field_of_view / 2));
	

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

	return ((void *)1);

}

static int	init_game(t_game *game)
{

	get_textures(game->conn, game->vars->textures);
	if (!init_player(game))
		return -1;
	game->vars->num_rays = game->vars->screen_width / RAY_WIDTH;
	game->rays = malloc(game->vars->num_rays * sizeof(t_ray));
	if (!game->rays)
		return -1;
	ft_bzero(game->rays, sizeof(t_ray));
	game->update = 0;
	printf("num_rays is: %d\n", game->vars->num_rays);
	return 0;

}


/*
** called many times per second (imitating frames per second) to:
** 1 - create an image
** 2 - update game data (if player pos has changed)
** 3 - fill image with updated data
** 4 - dump image data onto window
** 5 - clear image
*/
static int render_game(void *game) 
{
	t_game *g;

	g = (t_game *)game;
	g->conn->image.img = mlx_new_image(g->conn->mlx, g->vars->screen_width, g->vars->screen_height);
	g->conn->image.addr = mlx_get_data_addr(g->conn->image.img, &g->conn->image.bpp, 
					&g->conn->image.line_length, &g->conn->image.endian);
	
	if (g->update) //only update if keypress event has been triggered
	{
		update(g);
		g->update = 0;
	}
	// printf("get_color -> g_line is: %f\n", g->player->play_pos[0]);
	// printf("get_color -> g_col is: %f\n", g->player->play_pos[1]);
	//TODO: render / draw
	draw_2d_map(g);

	draw_player(g->conn, g->player);

	draw_direction_line(g->conn, g->player); //temporal function, to test the rotation

	//dump data from image to window
	mlx_put_image_to_window(g->conn->mlx, g->conn->win, g->conn->image.img, 0, 0);

	//destroy image
	mlx_destroy_image(g->conn->mlx, g->conn->image.img);
	
	return 0;
	
}


char	execute(t_game *game)
{
	if (!create_connection(game) || init_game(game) == -1)
		return -1;
	mlx_hook(game->conn->win, 2, 1L<<0, key_press, game); 
	mlx_hook(game->conn->win, 3, 1L<<1, key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game);
	mlx_loop_hook(game->conn->mlx, render_game, game);
	// if (!mlx_loop_hook(game->conn->mlx, render_game, game)) //constant running function
	// 	return -1;
	mlx_loop(game->conn->mlx);

	return (0);
}
