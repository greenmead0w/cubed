/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 20:48:39 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/15 21:06:28 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static	int	find_tile_size(int cols, int rows, int flag)
{
	int	width_t;
	int	height_t;
	int	new_tile;

	if (!flag)
	{
		width_t = MAX_SCREEN_WIDTH / cols;
		height_t = MAX_SCREEN_HEIGHT / rows;
	}
	else
	{
		width_t = (MAX_SCREEN_WIDTH / 4) / cols;
		height_t = (MAX_SCREEN_HEIGHT / 4) / rows;
	}
	if (width_t > height_t)
		new_tile = height_t;
	else
		new_tile = width_t;
	if (new_tile > 1 && new_tile % 2 == 1)
		new_tile--;
	return (new_tile);
}

static	void	get_window_size(t_vars *vars, int min_tile)
{
	int	big_tile;

	if (vars->map_cols * TILE_SIZE > MAX_SCREEN_WIDTH
		|| vars->map_rows * TILE_SIZE > MAX_SCREEN_HEIGHT)
	{
		vars->screen_width = MAX_SCREEN_WIDTH;
		vars->screen_height = MAX_SCREEN_HEIGHT;
		big_tile = find_tile_size(vars->map_cols, vars->map_rows, 0);
		if (vars->map_cols * MINI_TILE > MAX_SCREEN_WIDTH / 4
			|| vars->map_rows * MINI_TILE > MAX_SCREEN_HEIGHT / 4)
			min_tile = find_tile_size(vars->map_cols, vars->map_rows, 1);
		vars->big_tile = big_tile;
	}
	else
	{
		vars->screen_width = vars->map_cols * TILE_SIZE;
		vars->screen_height = vars->map_rows * TILE_SIZE;
		vars->big_tile = TILE_SIZE;
	}
	if (min_tile && min_tile < MINI_TILE)
		vars->min_tile = min_tile;
	else
		vars->min_tile = MINI_TILE;
}

static void	*open_connection(t_conn *conn, t_vars *vars)
{
	conn->mlx = mlx_init();
	if (!conn->mlx)
		return ((void *) 1);
	get_window_size(vars, 0);
	conn->win = mlx_new_window(conn->mlx, vars->screen_width,
			vars->screen_height, "cubed");
	if (!conn->win)
		return ((void *) 1);
	return ((void *) 0);
}

void	*create_connection(t_game *game)
{
	game->conn = malloc(sizeof(t_conn));
	if (!game->conn)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return ((void *) 1);
	}
	ft_bzero(game->conn, sizeof(t_conn));
	if (open_connection(game->conn, game->vars))
	{
		write(2, OPEN_CONN, ft_strlen(OPEN_CONN));
		return ((void *) 1);
	}
	return ((void *) 0);
}
