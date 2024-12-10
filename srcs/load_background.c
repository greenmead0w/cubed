/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:04:30 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 21:47:04 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	text(char value, t_game *p, int i, int j)
{
	int	x;
	int	y;

	x = j * 64;
	y = i * 64;
	if (value == '1')
	{
		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->vars->textures[NORTH], x, y);
	}
	if (value == '0')
		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->vars->textures[SOUTH], x, y);
/*	if (value == 'C')
	{
		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->textures[ZERO], x, y);
		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->textures[COLL], x, y);
	}
*/	if (ft_strchr(SET_2, value))
		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->vars->textures[EAST], x, y);
//	if (value == 'E')
//		IMAGE_TO_WINDOW(p->conn->mlx, p->conn->win, p->textures[EXIT], x, y);
}

void	load_background(t_game *game)
{
	int		i;
	int		j;
	char	**map;

	map = game->vars->game_map;
	i = 0;
	while (i < game->vars->map_rows)
	{
		j = 0;
		while (j < game->vars->map_cols)
		{
			text(map[i][j], game, i, j);
			j++;
		}
		i++;
	}
}
