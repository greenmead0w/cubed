/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:46:10 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/23 19:49:49 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	free_textures(t_conn *conn, t_texture **ptr, int counter)
{
	int	i;

	i = 0;
	while (i < counter)
	{
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
