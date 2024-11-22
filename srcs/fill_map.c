/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:33:13 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 21:39:25 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdlib.h>

void	fill_map(t_game *game, char *line)	 
{
	int static	row;
	
	game->map[row] = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!game->map[row])
		return (-1);
	ft_strcpy(game->map[row], line);
	row++;
}
