/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:58:14 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 21:44:41 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "stdlib.h"

void	free_simple_pointer(void *ptr)
{
	if (ptr)
		free(ptr);
}

static void	free_double_pointer(void **ptr)
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

void	free_all_game(t_game *game)
{
	if (game)
	{
		free_double_pointer(game->textures);
		free_color_list(game->color_root);
		free_double_pointer(game->map);
		free_double_pointer(game->game_map);
		free(game);
	}
}
