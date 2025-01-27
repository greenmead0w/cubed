/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_conn_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:52:38 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 19:38:50 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"
#include <stdlib.h>

int	ft_close_conn(t_game *game)
{
	free_all_game(game);
	// if (game->player->health <= 0)
	// 	write(1, HEALTH, ft_strlen(HEALTH));
	exit (0);
	return (0);
}
