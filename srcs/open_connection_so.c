/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 20:03:11 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/02/22 09:58:34 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libx.h"
#include <stdlib.h>

void	*open_connection(t_connection *my_conn, t_vars *vars)
{
	int	width;
	int	heigth;

	my_conn->mlx = mlx_init();
	if (!my_conn->mlx)
		return ((void *) 0);
	width = vars->columns * 64;
	heigth = vars->rows * 64;
	my_conn->win = mlx_new_window(my_conn->mlx, width, heigth, "so_long");
	if (!my_conn->win)
	{
		free(my_conn->mlx);
		my_conn->mlx = 0;
		return ((void *) 0);
	}
	return ((void *) 1);
}
