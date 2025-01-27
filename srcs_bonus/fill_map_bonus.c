/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 21:33:13 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 19:38:04 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

char	fill_map(t_vars *vars, char *line)
{
	static int	row;

	vars->map[row] = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!vars->map[row])
		return (-1);
	ft_strcpy(vars->map[row], line);
	row++;
	return (0);
}
