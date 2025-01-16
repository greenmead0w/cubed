/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:39:26 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/14 20:25:42 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_color	*generate_and_add_node(t_game *game)
{
	t_color	*color;

	color = ft_lstnew();
	if (color)
		ft_lstadd_back(&game->color_root, color);
	else
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
	return (color);
}

/*
**	he modificado -->  count_digits recibia parametro char **,
**	por lo que a pesar de utilizar una temporal
**	se estaba modificando line despues de contar digitos
*/
static int	take_partial_color(char **line)
{
	int		partial_color;
	int		size;
	char	*partial_color_str;

	size = count_digits(*line);
	partial_color_str = create_string(line, size);
	if (!partial_color_str)
		return (-1);
	partial_color = ft_atoi(partial_color_str);
	free_simple_pointer(partial_color_str);
	if (partial_color > 255)
	{
		write(2, COLOR, ft_strlen(COLOR));
		return (-1);
	}
	return (partial_color);
}

char	fill_colors_list(char *line, t_game *game)
{
	t_color	*color;

	color = generate_and_add_node(game);
	if (!color)
		return (-1);
	color->cf = *line;
	line++;
	while (*line == ' ')
		line++;
	color->r_color = take_partial_color(&line);
	if (color->r_color == -1)
		return (-1);
	color->g_color = take_partial_color(&line);
	if (color->g_color == -1)
		return (-1);
	color->b_color = take_partial_color(&line);
	if (color->b_color == -1)
		return (-1);
	return (0);
}
