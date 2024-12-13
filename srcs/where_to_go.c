/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   where_i_am.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:55:35 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/11 20:53:05 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

// void	where_i_am(t_params *params)
// {
// 	int	i;
// 	int	j;

// 	i = params->vars->play_pos[0];
// 	j = params->vars->play_pos[1];
// 	if (params->vars->sign == 1)
// 	{
// 		params->vars->map[i][j] = 'E';
// 		mlx_put_image_to_window(params->conn->mlx, params->conn->win, \
// 				params->imgs[EXIT], 64 * j, 64 * i);
// 		params->vars->sign = 0;
// 	}
// 	else
// 	{
// 		params->vars->map[i][j] = '0';
// 		mlx_put_image_to_window(params->conn->mlx, params->conn->win, \
// 				params->imgs[ZERO], 64 * j, 64 * i);
// 	}
// }

// void	where_i_go(t_params *params)
// {
// 	int	i;
// 	int	j;

// 	i = params->vars->play_pos[0];
// 	j = params->vars->play_pos[1];
// 	if (params->vars->map[i][j] == 'C')
// 		params->vars->coll_nbr++;
// 	if (params->vars->map[i][j] == 'E')
// 	{
// 		if (params->vars->coll_nbr == params->vars->coll_max_nbr)
// 		{
// 			free_all(params);
// 			exit (0);
// 		}
// 		else
// 			params->vars->sign = 1;
// 	}
// 	params->vars->map[i][j] = 'P';
// 	mlx_put_image_to_window(params->conn->mlx, params->conn->win, \
// 			params->imgs[PLAYER], 64 * j, 64 * i);
// }
