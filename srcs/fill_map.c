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

char	fill_map(t_game *game, char *line)	 
{
	static int	row; //uso de staticas sin problemas no?
	
	game->map[row] = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!game->map[row])
		return (-1);
	ft_strcpy(game->map[row], line);
	row++;
	return 0;
}
