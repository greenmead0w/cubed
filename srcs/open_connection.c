/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:48:39 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/08 21:49:07 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	*open_connection(t_conn *conn, t_vars *vars)
{
	conn->mlx = mlx_init();
	if (!conn->mlx)
		return ((void *) 1);
	vars->screen_width = vars->map_cols * TILE_SIZE;
	vars->screen_height = vars->map_rows * TILE_SIZE;
	conn->win = mlx_new_window(conn->mlx, vars->screen_width,
			vars->screen_height, "cubed");
	if (!conn->win)
	{
		free(conn->mlx);
		conn->mlx = 0;
		return ((void *) 1);
	}
	return ((void *) 0);
}

void	*create_connection(t_game *game)
{
	game->conn = malloc(sizeof(t_conn));
	if (!game->conn)
	{
		free_all_game(game);
		return ((void *)1);
	}
	ft_bzero(game->conn, sizeof(t_conn));
	if (open_connection(game->conn, game->vars))
	{
		free_all_game(game);
		return ((void *)1);
	}
	return ((void *) 0);
}
