/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_rectangular_map_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 20:46:32 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 19:57:39 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

// linea 8 - ultima linea no va a tener break of line
static char	*create_rectangular_line(char *line, int max_len)
{
	char	*rect_line;

	rect_line = malloc(max_len + 1);
	if (rect_line == NULL)
		return (NULL);
	ft_bzero(rect_line, max_len + 1);
	ft_strlcpy(rect_line, line, ft_strlen(line) + 1);
	if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
		rect_line[ft_strlen(rect_line) - 1] = ' ';
	ft_memset(rect_line + ft_strlen(line), ' ', max_len - ft_strlen(line));
	rect_line[max_len] = '\0';
	return (rect_line);
}

char	**make_rectangular_map(char **map, int lines, int max_len)
{
	int		i;
	char	**rect;

	rect = malloc(sizeof(char *) * (lines + 1));
	if (rect == NULL)
		return (rect);
	i = 0;
	while (i < lines)
	{
		rect[i] = create_rectangular_line(map[i], max_len);
		if (rect[i] == NULL)
		{
			free_double_pointer((void **)rect);
			return (NULL);
		}
		i++;
	}
	rect[lines] = NULL;
	return (rect);
}
