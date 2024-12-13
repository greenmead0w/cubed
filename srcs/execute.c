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

char	execute(t_game *game)
{
	game->conn = malloc(sizeof(t_conn)); //AÑADIDO
	if (!game->conn)//AÑADIDO
	{
		free_all_game(game);//AÑADIDO
		return -1;//AÑADIDO
	}//AÑADIDO
	ft_bzero(game->conn, sizeof(t_conn)); //AÑADIDO
	if (!open_connection(game->conn, game->vars))
	{
		printf("error open_connection()\n"); //solo añadido para debuggear
		free_all_game(game);
		return (-1);
	}
	printf("game->vars->play_pos[0] is: %d\n", game->vars->play_pos[0]);
	printf("game->vars->play_pos[1] is: %d\n", game->vars->play_pos[1]);
	get_textures(game->conn, game->vars->textures);
	load_background(game);
	find_play_pos(game->vars->game_map, game->vars->map_rows, \
			game->vars->map_cols, game->vars->play_pos);
	mlx_key_hook(game->conn->win, &key_hook, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game->vars);
	mlx_loop(game->conn->mlx);
	return (0);
}
