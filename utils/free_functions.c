/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:58:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/13 19:50:22 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

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
	mlx_destroy_window(conn->mlx, conn->win);
	mlx_destroy_display(conn->mlx);
	free_simple_pointer(conn->mlx);
	free_simple_pointer(conn);
}

void	free_all_game(t_game *game)
{
	if (game)
	{
		free_textures(game->conn, game->vars->textures, 4);
		free_color_list(game->color_root);
		free_double_pointer((void **)game->vars->map);
		free_double_pointer((void **)game->vars->game_map);
		free(game->vars);
		if (game->conn)
			free_mlx(game->conn);
		free(game->player);
		free(game->rays);
		free(game);
	}
}
