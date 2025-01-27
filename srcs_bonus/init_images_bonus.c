/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:04:34 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 22:05:36 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static char	init_images_by_type(t_texture **type, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		type[i] = malloc(sizeof(t_texture));
		if (!type[i])
			return (-1);
		ft_bzero(type[i], sizeof(t_texture));
		i++;
	}
	return (0);
}

char	init_images(t_game *game)
{
	int	control_var;

	control_var = 0;
	if (init_images_by_type(game->vars->walls, SIDES))
		control_var = -1;
	if (init_images_by_type(game->vars->animate_empty, SIDES))
		control_var = -1;
	if (init_images_by_type(game->vars->animate_cheer, SIDES))
		control_var = -1;
	if (control_var)
		free_all_game(game);
	return (control_var);
}
