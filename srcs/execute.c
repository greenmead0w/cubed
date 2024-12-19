/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 20:43:09 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	*open_connection(t_conn *conn, t_vars *vars)
{
	int	width;
	int	heigth;

	conn->mlx = mlx_init();
	if (!conn->mlx)
		return ((void *) 0);
	width = vars->map_cols * TILE_SIZE;
	heigth = vars->map_rows * TILE_SIZE;
	conn->win = mlx_new_window(conn->mlx, width, heigth, "cubed");
	if (!conn->win)
	{
		free(conn->mlx);
		conn->mlx = 0;
		return ((void *) 0);
	}
	return ((void *) 1);
}

void init_player_data(t_vars *vars)
{
	vars->turn_direction = 0;
	vars->walk_direction = 0;
	vars->rotation_angle = M_PI / 2; //90 degrees in radians
	vars->rotation_speed = 2 *(M_PI / 180); //equivalent of 2 degrees in radians
	vars->move_speed = 2; //pixels per key press

}

// static void draw(t_game *game)
// {
// 	load_background(game); //render map

// }

static void *create_connection(t_game *game)
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

static void	first_draw(t_game *game)
{
	get_textures(game->conn, game->vars->textures);
	init_player_data(game->vars);
	initial_player_pos(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->vars->play_pos);
	render_map(game);

}

// static void update_player_pos(t_vars *vars)
// {


// }

// static void draw(t_game *game)
// {
// 	update_player_pos(game->vars);

// }

char	execute(t_game *game)
{
	if (!create_connection(game))
		return -1;
	first_draw(game);
	mlx_hook(game->conn->win, 2, 1L<<0, &key_press, game); 
	//mlx_hook(game->conn->win, 3, 1L<<1, &key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game->vars);
	//mlx_loop_hook(game->conn->mlx, &draw, game); //constant running function
	mlx_loop(game->conn->mlx);
	return (0);
}
