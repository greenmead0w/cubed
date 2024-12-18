/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:24:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/11 20:51:55 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include <stdio.h>


static void move_player(t_vars *vars, int x, int y)
{
	int new_x;
	int new_y;

	new_x = vars->play_pos[0] + x;
	new_y = vars->play_pos[1] + y;
	//1-change old player position to 0
	vars->game_map[vars->play_pos[0]][vars->play_pos[1]] = '0';
	//2-change new player position to NSEW(?)
	vars->play_pos[0] = new_x;
	vars->play_pos[1] = new_y;
	vars->game_map[new_x][new_y] = 'N'; //hardcodeado aquí, solo para ver lógica movimiento
}

int	key_press(int keycode, t_game *game)
{
	int		i;
	int		j;
	char	**map;


	i = game->vars->play_pos[0];
	j = game->vars->play_pos[1];
	map = game->vars->game_map;
	if (keycode == XK_Escape)
		exit (0);
	if (keycode ==  XK_w && map[i - 1][j] != '1')
		move_player(game->vars, -1, 0);
	else if (keycode ==  XK_s && map[i + 1][j] != '1')
		move_player(game->vars, +1, 0);
	else if (keycode ==  XK_a && map[i][j - 1] != '1')
		move_player(game->vars, 0, -1);
	else if (keycode ==  XK_d && map[i][j + 1] != '1')
		move_player(game->vars, 0, +1);
	load_background(game); //rerender map
	return (0);
}

/*int	key_release(int keycode, t_game *game)
{
	// int		i;
	// int		j;
	// char	**map;


	// i = game->vars->play_pos[0];
	// j = game->vars->play_pos[1];
	// map = game->vars->game_map;
	// if (keycode == XK_Escape)
	// 	exit (0);
	// if (keycode ==  XK_w && map[i - 1][j] != '1')
	// 	move_player(game->vars, -1, 0);
	// else if (keycode ==  XK_s && map[i + 1][j] != '1')
	// 	move_player(game->vars, +1, 0);
	// else if (keycode ==  XK_a && map[i][j - 1] != '1')
	// 	move_player(game->vars, 0, -1);
	// else if (keycode ==  XK_d && map[i][j + 1] != '1')
	// 	move_player(game->vars, 0, +1);
	// load_background(game); //rerender map
	// return (0);
}*/