/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:33:13 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 18:37:26 by mzuloaga         ###   ########.fr       */
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
	return (0);
}
