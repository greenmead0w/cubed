/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:33:36 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 21:37:43 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "definitions.h"

int	find_play_pos(char **map, int rows, int columns, int *player_pos)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < columns)
		{
			if (ft_strchr(SET_2, map[i][j]))
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
