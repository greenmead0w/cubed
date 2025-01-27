/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cubed_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:25:06 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 21:46:11 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static char	generate_and_initialize_game(t_game **game, \
		t_track_items **track_elements)
{
	*game = malloc(sizeof(t_game));
	*track_elements = malloc(sizeof(t_track_items));
	if (!*game || !*track_elements)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		free_simple_pointer(*game);
		free_simple_pointer(*track_elements);
		return (-1);
	}
	ft_bzero(*game, sizeof(t_game));
	ft_bzero(*track_elements, sizeof(t_track_items));
	(*game)->vars = malloc(sizeof(t_vars));
	if (!(*game)->vars)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		free_simple_pointer((*game)->vars);
		free_simple_pointer(*game);
		free_simple_pointer(*track_elements);
		return (-1);
	}
	ft_bzero((*game)->vars, sizeof(t_vars));
	return (0);
}

static char	check_and_parse(char *file, t_game *game, \
		t_track_items *track_elems)
{
	if (check(file, game, track_elems))
	{
		free_simple_pointer(track_elems);
		free_simple_pointer(game->vars);
		free_simple_pointer(game);
		return (-1);
	}
	free_simple_pointer(track_elems);
	if (init_images(game))
		return (-1);
	if (parse(file, game))
	{
		free_all_game(game);
		return (-1);
	}
	if (check_map(game->vars))
	{
		free_all_game(game);
		return (-1);
	}
	return (0);
}

static char	play_game(char *file)
{
	t_game			*game;
	t_track_items	*track_elements;

	game = (void *) 0;
	track_elements = (void *) 0;
	if (generate_and_initialize_game(&game, &track_elements))
		return (-1);
	if (check_and_parse(file, game, track_elements))
		return (-1);
	if (execute(game))
		return (-1);
	free_all_game(game);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (play_game(argv[1]))
			return (-1);
	}
	else
	{
		write(2, ARG_NUM, ft_strlen(ARG_NUM));
		return (-1);
	}
	return (0);
}
