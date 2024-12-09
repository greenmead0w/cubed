/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 10:24:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/02/23 07:04:22 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libx.h"
#include "ft_printf.h"

static void	move_up(t_params *params)
{
	where_i_am(params);
	params->vars->play_pos[0] -= 1;
	where_i_go(params);
	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_down(t_params *params)
{
	where_i_am(params);
	params->vars->play_pos[0] += 1;
	where_i_go(params);
	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_left(t_params *params)
{
	where_i_am(params);
	params->vars->play_pos[1] -= 1;
	where_i_go(params);
	ft_printf("%i\n", ++(params->vars->moves));
}

static void	move_right(t_params *params)
{
	where_i_am(params);
	params->vars->play_pos[1] += 1;
	where_i_go(params);
	ft_printf("%i\n", ++(params->vars->moves));
}

int	key_hook(int keycode, t_params *params)
{
	int		i;
	int		j;
	char	**map;

	find_play_pos(params->vars->map, params->vars->rows, \
			params->vars->columns, params->vars->play_pos);
	i = params->vars->play_pos[0];
	j = params->vars->play_pos[1];
	map = params->vars->map;
	if (keycode == 53)
	{
		free_all(params);
		exit (0);
	}
	if ((keycode == 13 || keycode == 126) && map[i - 1][j] != '1')
		move_up(params);
	else if ((keycode == 1 || keycode == 125) && map[i + 1][j] != '1')
		move_down(params);
	else if ((keycode == 0 || keycode == 123) && map[i][j - 1] != '1')
		move_left(params);
	else if ((keycode == 2 || keycode == 124) && map[i][j + 1] != '1')
		move_right(params);
	return (0);
}
