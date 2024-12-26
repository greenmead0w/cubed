/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:24:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/26 18:49:08 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>


/*static void move_player(t_vars *vars, t_player *player, int x, int y)
{
	int new_x;
	int new_y;

	new_x = player->play_pos[0] + x;
	new_y = player->play_pos[1] + y;
	//1-change old player position to 0
	vars->game_map[player->play_pos[0]][player->play_pos[1]] = '0';
	//2-change new player position to NSEW(?)
	player->play_pos[0] = new_x;
	player->play_pos[1] = new_y;
	vars->game_map[new_x][new_y] = 'N'; //hardcodeado aquí, solo para ver lógica movimiento
} */



int	key_press(int keycode, t_game *game)
{
	printf("key press called \n");
	if (keycode == XK_Escape)
		ft_close_conn(game);
	if (keycode ==  XK_w)
		game->player->walk_direction = 'w';
	else if (keycode ==  XK_s)
		game->player->walk_direction = 's';
	else if (keycode ==  XK_a)
		game->player->walk_direction = 'a';
	else if (keycode ==  XK_d)
		game->player->walk_direction = 'd';
	else if (keycode ==  XK_Left)
		game->player->turn_direction = -1;
	else if (keycode ==  XK_Right)
		game->player->turn_direction = 1;
	if (game->player->walk_direction != '0'
		|| game->player->turn_direction != 0)
		game->update = 1;
	printf("kpressed; game->update is: %d\n", game->update);
	return (0);
}

int	key_release(int kc, t_game *game)
{
	printf("key release called \n");
	if (kc ==  XK_w || kc == XK_s || kc == XK_a || kc == XK_d)
		game->player->walk_direction = '0';
	else if (kc == XK_Left || kc == XK_Right)
		game->player->turn_direction = 0;
	return (0);
}