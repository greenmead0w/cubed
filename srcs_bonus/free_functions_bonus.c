/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:58:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 21:02:45 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

//Igual hay que añadir una función que se llama cuando hay un error y exiteamos?
void	free_simple_pointer(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_double_pointer(void **ptr)
{
	void	**run;

	if (ptr)
	{
		run = ptr;
		while (*run)
			free_simple_pointer(*run++);
		free(ptr);
	}
}

static void	free_color_list(t_color *color_root)
{
	t_color	*run;
	t_color	*previous;

	if (color_root)
	{
		run = color_root;
		while (run)
		{
			previous = run;
			run = run->next;
			free(previous);
		}
	}
}

void	free_mlx(t_conn *conn)
{
	if (conn->image.ptr)
		mlx_destroy_image(conn->mlx, conn->image.ptr);
	mlx_destroy_window(conn->mlx, conn->win);
	mlx_destroy_display(conn->mlx);
	free_simple_pointer(conn->mlx);
	free_simple_pointer(conn);
}

void	free_all_game(t_game *game)
{
	if (game)
	{
		free_color_list(game->color_root);
		if (game->vars)
		{
			free_images(game->conn, game->vars->walls, 4, 1);
			free_images(game->conn, game->vars->animate_empty, 4, 0);
			free_images(game->conn, game->vars->animate_cheer, 4, 0);
			free_double_pointer((void **)game->vars->map);
			free_double_pointer((void **)game->vars->game_map);
		}
		free_simple_pointer(game->vars);
		if (game->conn)
			free_mlx(game->conn);
		free_simple_pointer(game->player);
		free_simple_pointer(game->rays);
		free_simple_pointer(game);
	}
}
