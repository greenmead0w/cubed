/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:58:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/08 17:57:50 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "utils.h"
# include <stdlib.h>

//Igual hay que añadir una función que se llama cuando hay un error y exiteamos?
void	free_simple_pointer(void *ptr)
{
	if (ptr)
		free(ptr);
}

/*
**	he cambiado a no statica para poder llamarlo en check_map.c 
**	(si falla malloc en make_rectangular_map)
*/
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

void	free_textures(t_conn *conn, t_texture **ptr, int counter)
{
	int i;

	i = 0;
	while (i < counter)
	{
		if (ptr[i]->path)
			free(ptr[i]->path);
		if (ptr[i]->img.ptr)
		{
			if (conn)
				mlx_destroy_image(conn->mlx, ptr[i]->img.ptr);
			else
				free(ptr[i]->img.ptr); //dudas de si esto tiene sentido
		}
		free(ptr[i]);
		i++;
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

void free_mlx(t_conn *conn)
{
	mlx_destroy_window(conn->mlx, conn->win);
	mlx_destroy_display(conn->mlx);
	free(conn->mlx);
	free(conn);
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
