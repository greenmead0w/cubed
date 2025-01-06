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

/*
** Angles in computer graphics increase clockwise
*/
static void initial_player_angle(t_player *player, char letter)
{
	if (letter == 'S')
		player->rotation_angle = 90 * M_PI / 180;
	else if (letter == 'W')
		player->rotation_angle = 180 * M_PI / 180;
	else if (letter == 'N')
		player->rotation_angle = 270 * M_PI / 180;
	else if (letter == 'E')
		player->rotation_angle = 360 * M_PI / 180;

}

/*
**+ 0.5 to center in the tile
*/
int	initial_player_data(char **map, int rows, int columns, t_player *player)
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
				player->play_pos[0] = i + 0.5;
				player->play_pos[1] = j + 0.5;
				initial_player_angle(player, map[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (-1);
}
