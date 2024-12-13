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

// static void	move_up(t_vars *vars)
// {
// 	(void) vars;
// //	where_i_am(params);
// 	vars->play_pos[0] -= 1;
// //	where_i_go(params);
// //	ft_printf("%i\n", ++(params->vars->moves));
// 	printf("up\n");
// }

// static void	move_down(t_vars *vars)
// {
// 	(void) vars;
// //	where_i_am(params);
// 	vars->play_pos[0] += 1;
// //	where_i_go(params);
// //	ft_printf("%i\n", ++(params->vars->moves));
// 	printf("down\n");
// }

// static void	move_left(t_vars *vars)
// {
// 	(void) vars;
// //	where_i_am(params);
// 	vars->play_pos[1] -= 1;
// //	where_i_go(params);
// //	ft_printf("%i\n", ++(params->vars->moves));
// 	printf("left\n");
// }

// static void	move_right(t_vars *vars)
// {
// 	(void) vars;
// //	where_i_am(params);
// 	vars->play_pos[1] += 1;
// //	where_i_go(params);
// //	ft_printf("%i\n", ++(params->vars->moves));
// 	printf("right\n");
// }

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

int	key_hook(int keycode, t_game *game)
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


// int	key_hook(int keycode, t_game *game)
// {
// 	int		i;
// 	int		j;
// 	char	**map;

// 	printf("key_hook. keycode is: %d\n", keycode);
 	/*find_play_pos(vars->game_map, vars->map_rows, \
 	 		vars->map_cols, vars->play_pos);*/
// 	i = game->vars->play_pos[0];
// 	j = game->vars->play_pos[1];
// 	map = game->vars->game_map;
// 	if (keycode == XK_Escape)
// 	{
// //		free_all(params);
// 		exit (0);
// 	}
// 	if (keycode ==  XK_w && map[i - 1][j] != '1')
// 	{
// 		// move_up(vars);
// 		move_player(game->vars, -1, 0);
// 	}
// 	else if (keycode ==  XK_s && map[i + 1][j] != '1')
// 	{
// 		//move_down(vars);
// 		move_player(game->vars, +1, 0);
// 	}
// 	else if (keycode ==  XK_a && map[i][j - 1] != '1')
// 	{
// 		//move_left(vars);
// 		move_player(game->vars, 0, -1);
// 	}
// 	else if (keycode ==  XK_d && map[i][j + 1] != '1')
// 	{
// 		//move_right(vars);
// 		move_player(game->vars, 0, +1);
// 	}
// 	load_background(game); //rerender map
// 	return (0);
// }