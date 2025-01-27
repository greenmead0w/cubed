/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 20:05:12 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 19:37:29 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static void	draw_all_elements(t_game *game)
{
	draw_ceiling(game);
	draw_floor(game);
	draw_ray_cast(game, 0);
	draw_2d_map(game);
	draw_all_rays(game);
	draw_player(game->conn, game->player, game->vars);
	draw_health(game);
}

/*
** called many times per second (imitating frames per second) to:
** 1 - create an image
** 2 - update game data (if player pos has changed / keyPressed)
** 3 - fill image with updated data
** 4 - dump image data onto window
** 5 - clear image

** NOT CHECKING IF MLX_NEW_IMAGE() OR MLX_GET_DATA_ADDR ERROR
*/
static int	render_game(void *game)
{
	t_game	*g;

	g = game;
	g->conn->image.ptr = mlx_new_image(g->conn->mlx,
			g->vars->screen_width, g->vars->screen_height);
	if (!g->conn->image.ptr)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	g->conn->image.addr = mlx_get_data_addr(g->conn->image.ptr,
			&g->conn->image.bpp, &g->conn->image.line_length,
			&g->conn->image.endian);
	if (!g->conn->image.addr)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	update(g);
	set_texture_to_display(g->vars);
	draw_all_elements(g);
	IMAGE_TO_WINDOW(g->conn->mlx, g->conn->win,
		g->conn->image.ptr, 0, 0);
	mlx_destroy_image(g->conn->mlx, g->conn->image.ptr);
	g->conn->image.ptr = NULL;
	return (0);
}

char	execute(t_game *game)
{
	if (create_connection(game) || init_game(game))
	{
		free_all_game(game);
		return (-1);
	}
	mlx_hook(game->conn->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->conn->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->conn->win, 4, 1L << 2, mouse_press, game);
	mlx_hook(game->conn->win, 5, 1L << 3, mouse_release, game);
	mlx_hook(game->conn->win, 17, 0, ft_close_conn, game);
	mlx_loop_hook(game->conn->mlx, render_game, game);
	mlx_loop(game->conn->mlx);
	return (0);
}
