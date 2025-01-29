/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doors_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:19:38 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/28 21:36:21 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static int is_invalid_door(char **map, int i, int j)
{
//if (i == 0 || i == lines - 1 || j == 0 || j == max_len - 2)
//				return (write(2, "Error: Door on map border\n", ft_strlen(error)));
	if (!((map[i][j - 1] == '1' && map[i][j + 1] == '1') || \
	(map[i - 1][j] == '1' && map[i + 1][j] == '1')))
	{
		write(2, DOOR_NO_WALL, ft_strlen(DOOR_NO_WALL));
		return (-1);
	}
	if (map[i][j - 1] == 'D' || map[i][j + 1] == 'D' || \
	map[i - 1][j] == 'D' || map[i + 1][j] == 'D')
	{		
		write(2, ADJACENT_DOORS, ft_strlen(ADJACENT_DOORS));
		return (-1);
	}
	return (0);
}

int	check_doors(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'D' && is_invalid_door(map, i, j))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}
