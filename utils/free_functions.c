/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:58:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 22:15:55 by dpinedo-         ###   ########.fr       */
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

static void	free_double_pointer_ep(void **ptr)
{
	void	**run;

	if (ptr)
	{
		run = ptr;
		while (*run)
			free_simple_pointer(*run++);
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

void	free_all_game(t_game *game)
{
	if (game)
	{
		free_double_pointer_ep((void **)game->vars->textures);
		free_color_list(game->color_root);
		free_double_pointer((void **)game->vars->map);
		free_double_pointer((void **)game->vars->game_map);
		free(game);
	}
}
