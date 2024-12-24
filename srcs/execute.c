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

static void *init_player(t_game *game)
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
	game->player->move_speed = 2; //pixels per key press
	initial_player_data(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->player);
	game->player->dist_to_plane = 
	

	printf("turn_direction is: %c\n", game->player->turn_direction);
	printf("walk_direction is: %c\n", game->player->walk_direction);
	printf("rotation_angle is: %f\n", game->player->rotation_angle);
	printf("rotation_speed is: %f\n", game->player->rotation_speed);
	printf("move_speed is: %d\n", game->player->move_speed);
	printf("posX is: %f\n", game->player->play_pos[0]);
	printf("posY is: %f\n", game->player->play_pos[1]);

	return ((void *)1);

}

static int	init_game(t_game *game)
{
	get_textures(game->conn, game->vars->textures);
	if (!init_player(game))
		return -1;
	//render_map(game);
	return 0;

}


char	execute(t_game *game)
{
	if (!create_connection(game) || init_game(game) == -1)
		return -1;
	mlx_hook(game->conn->win, 2, 1L<<0, key_press, game); 
	mlx_hook(game->conn->win, 3, 1L<<1, key_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game);
	//mlx_loop_hook(game->conn->mlx, &draw, game); //constant running function
	mlx_loop(game->conn->mlx);
	return (0);
}
