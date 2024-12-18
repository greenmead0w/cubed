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
	width = vars->map_cols * 64;
	heigth = vars->map_rows * 64;
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

char	execute(t_game *game)
{
	game->conn = malloc(sizeof(t_conn));
	if (!game->conn)
	{
		free_all_game(game);
		return -1;
	}
	ft_bzero(game->conn, sizeof(t_conn));
	if (!open_connection(game->conn, game->vars))
	{
		printf("error open_connection()\n"); //solo añadido para debuggear
		free_all_game(game);
		return (-1);
	}
	printf("game->vars->play_pos[0] is: %d\n", game->vars->play_pos[0]);
	printf("game->vars->play_pos[1] is: %d\n", game->vars->play_pos[1]);
	get_textures(game->conn, game->vars->textures);
	init_player_data(game->vars);
	// printf("vars->turn_direction is: %d\n", game->vars->turn_direction);
	// printf("vars->walk_direction is: %d\n", game->vars->walk_direction);
	// printf("vars->rotation_angle is: %f\n", game->vars->rotation_angle);
	// printf("vars->rotation_speed is: %f\n", game->vars->rotation_speed);
	// printf("vars->move_speed is: %d\n", game->vars->move_speed);
	load_background(game);
	find_play_pos(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->vars->play_pos);
	//mlx_key_hook(game->conn->win, &key_hook, game);
	mlx_hook(game->conn->win, 2, 1L<<0, &key_press, game); 
	//mlx_hook(game->conn->win, 3, 1L<<1, &key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game->vars);
	mlx_loop(game->conn->mlx);
	return (0);
}
