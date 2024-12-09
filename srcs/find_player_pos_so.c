/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:33:36 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/02/22 11:41:18 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_play_pos(char **map, size_t rows, size_t columns, int *player_pos)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (map[i][j] == 'P')
			{
				player_pos[0] = i;
				player_pos[1] = j;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
