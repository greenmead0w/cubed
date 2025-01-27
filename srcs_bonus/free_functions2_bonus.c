/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:46:10 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/27 21:03:27 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	free_images(t_conn *conn, t_texture **ptr, int counter, int flag_walls)
{
	int	i;

	i = 0;
	while (i < counter)
	{
		if (flag_walls)
			free_simple_pointer(ptr[i]->path);
		if (ptr[i]->img.ptr)
		{
			if (conn)
				mlx_destroy_image(conn->mlx, ptr[i]->img.ptr);
			else
				free_simple_pointer(ptr[i]->img.ptr);
		}
		free_simple_pointer(ptr[i]);
		i++;
	}
}
