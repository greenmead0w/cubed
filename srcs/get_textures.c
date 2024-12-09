/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 22:41:23 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	get_textures(t_conn *con, void **textures)
{
	int	width;
	int	height;

	width = 64;
	height = 64;
	textures[NORTH] = XPM_TO_IMAGE(con->mlx, NORTH_W, &width, &height);
	textures[SOUTH] = XPM_TO_IMAGE(con->mlx, SOUTH_W, &width, &height);
	textures[EAST] = XPM_TO_IMAGE(con->mlx, EAST_W, &width, &height);
	textures[WEST] = XPM_TO_IMAGE(con->mlx, WEST_W, &width, &height);
}
