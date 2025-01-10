/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_others.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:44:14 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/10 12:44:52 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	put_pixel_to_image(t_conn *conn, int x, int y, int color)
{
	char	*dst;

	dst = conn->image.addr
		+ (y * conn->image.line_length + x * (conn->image.bpp / 8));
	*(unsigned int *)dst = color;
}

/*
**	used on mini_map.c to draw tile borders colors
*/
int	is_border_map(t_draw_2d *p, t_vars *vars)
{
	int	is_vert_border;
	int	is_horz_border;

	is_vert_border = (p->curr_x == p->start_x
			|| p->curr_x == p->start_x + vars->min_tile -1);
	is_horz_border = (p->curr_y == p->start_y
			|| p->curr_y == p->start_y + vars->min_tile -1);
	return (is_vert_border || is_horz_border);
}

/*
**  Using bitwise operations to go from 3 independent color 1-char-ints 
**  to 1 0x00RRGGBB color
**	used for getting the floor and the ceiling colors
*/
int	combine_rgb(t_color *color, char flag)
{
	t_color	*current;
	int		res_color;

	current = color;
	res_color = 0;
	while (current && current->cf != flag)
		current = current->next;
	if (current)
		res_color = current->r_color << 16 | current->g_color << 8
			| current->b_color;
	return (res_color);
}
