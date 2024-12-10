/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:24:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 20:32:36 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static void	move_up(t_vars *vars)
{
	(void) vars;
//	where_i_am(params);
	vars->play_pos[0] -= 1;
//	where_i_go(params);
//	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_down(t_vars *vars)
{
	(void) vars;
//	where_i_am(params);
	vars->play_pos[0] += 1;
//	where_i_go(params);
//	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_left(t_vars *vars)
{
	(void) vars;
//	where_i_am(params);
	vars->play_pos[1] -= 1;
//	where_i_go(params);
//	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_right(t_vars *vars)
{
	(void) vars;
//	where_i_am(params);
	vars->play_pos[1] += 1;
//	where_i_go(params);
//	ft_printf("%i\n", ++(params->vars->moves));
}

int	key_hook(int keycode, t_vars *vars)
{
	int		i;
	int		j;
	char	**map;

	find_play_pos(vars->game_map, vars->map_rows, \
			vars->map_cols, vars->play_pos);
	i = vars->play_pos[0];
	j = vars->play_pos[1];
	map = vars->game_map;
	if (keycode == 9)
	{
//		free_all(params);
		exit (0);
	}
	if ((keycode == 25) && map[i - 1][j] != '1')
		move_up(vars);
	else if ((keycode == 39) && map[i + 1][j] != '1')
		move_down(vars);
	else if ((keycode == 38) && map[i][j - 1] != '1')
		move_left(vars);
	else if ((keycode == 40) && map[i][j + 1] != '1')
		move_right(vars);
	return (0);
}
