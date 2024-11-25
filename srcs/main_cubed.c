/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cubed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:25:06 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/22 19:17:18 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h> //para debuggear (printf)

static char	generate_and_initialize_game(t_game **game, \
		t_track_items **track_elements)
{
	*game= malloc(sizeof(t_game));
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
	return (0);
}

static char	check_and_parse(char *file, t_game *game, \
		t_track_items *track_elems)
{
	if (check(file, game, track_elems))
	{
		free_simple_pointer(track_elems);
		free_simple_pointer(game);
		return (-1);
	}
	free_simple_pointer(track_elems);
	if (parse(file, game))
	{
		free_all_game(game);
		return (-1);
	}
	printf("error en check_map\n");
	if (check_map(game))
	{
		free_all_game(game);
		return (-1);
	}	
	return (0);
}

static char	play_game(char *file)
{
	t_game		*game;
	t_track_items	*track_elements;

	game = (void *) 0;
	track_elements = (void *) 0;
	if (generate_and_initialize_game(&game, &track_elements))
		return (-1);
	if (check_and_parse(file, game, track_elements))
		return (-1);

	char **temp_text = game->textures;
	int i = 0;
	while(temp_text[i] != NULL)
	{
		printf("texture[%d]: %s\n", i, temp_text[i]);
		i++;
	}
	t_color *temp = game->color_root;
	while(temp != NULL)
	{
		printf("ceiling or roof: %c\n", temp->cf);
		printf("r_color: %d\n", temp->r_color);
		printf("g_color: %d\n", temp->g_color);
		printf("b_color: %d\n", temp->b_color);
		temp = temp->next;
	}
	char **temp_map = game->game_map;
	i = 0;
	while(temp_map[i] != NULL)
	{
		printf("map line[%d]: %s\n", i, temp_map[i]);
		i++;
	}
	free_all_game(game);
	return (0);
}

/*
**	añadir mensaje de error si el número de argumentos es incorrecto y retornar -1?
**	si argc >2 retorna 0
** 
*/
int	main(int argc, char **argv)
{
	printf("argc is: %d\n", argc);
	printf("argv[0] is: %s\n", argv[0]);
	printf("argv[1] is: %s\n", argv[1]);
	printf("argv[2] is: %s\n", argv[2]);
	if (!argv[1])
		return (-1);
	if (argc == 2)
	{
		if (play_game(argv[1]))
			return (-1);
	}
	return (0);
}