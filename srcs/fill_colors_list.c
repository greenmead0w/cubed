/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_colors_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:39:26 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 21:43:51 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static t_color	*generate_and_add_node(t_game *game)
{
	t_color	*color;
	
	color = ft_lstnew();
	if (color)
		ft_lstadd_back(&game->color_root, color);
	return (color);
}

/*
** he modificado -->  count_digits recibia parametro char **, por lo que a pesar de utilizar una temporal
** se estaba modificando line despues de contar digitos
*/
static int	take_partial_color(char **line)
{
	int	partial_color;
	int	size;
	char	*partial_color_str;

	while (**line != ',' && **line != '\n' && **line)
	{
		size = count_digits(*line); //modificado
		partial_color_str = create_string(line, size);
		if (!partial_color_str)
			return (-1); //printear malloc error antes de salir?
		partial_color = ft_atoi(partial_color_str);
		if (!partial_color)
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
