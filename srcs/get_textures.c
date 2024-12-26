/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/26 08:31:52 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_textures(t_conn *con, void **textures)
{
	int	width;
	int	height;

	width = TILE_SIZE;
	height = TILE_SIZE;
	textures[WALL] = XPM_TO_IMAGE(con->mlx, NORTH_W, &width, &height);
	textures[SPACE_T] = XPM_TO_IMAGE(con->mlx, SPACE_W, &width, &height);
	textures[PLAYER_T] = XPM_TO_IMAGE(con->mlx, EAST_W, &width, &height);
	textures[WEST] = XPM_TO_IMAGE(con->mlx, WEST_W, &width, &height);
}
