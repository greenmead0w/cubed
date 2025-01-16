/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:24:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:22:10 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>

int	key_press(int keycode, t_game *game)
{
	if (keycode == XK_ESCAPE)
		ft_close_conn(game);
	if (keycode == XK_W)
		game->player->walk_direction = 'w';
	else if (keycode == XK_S)
		game->player->walk_direction = 's';
	else if (keycode == XK_A)
		game->player->walk_direction = 'a';
	else if (keycode == XK_D)
		game->player->walk_direction = 'd';
	else if (keycode == XK_LEFT)
		game->player->turn_direction = -1;
	else if (keycode == XK_RIGHT)
		game->player->turn_direction = 1;
	if (game->player->walk_direction != '0'
		|| game->player->turn_direction != 0)
		game->update = 1;
	return (0);
}

int	key_release(int kc, t_game *game)
{
	if (kc == XK_W || kc == XK_S || kc == XK_A || kc == XK_D)
		game->player->walk_direction = '0';
	else if (kc == XK_LEFT || kc == XK_RIGHT)
		game->player->turn_direction = 0;
	return (0);
}
