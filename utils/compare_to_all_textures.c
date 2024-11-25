/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_to_all_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:37:19 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 16:29:46 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** retorna 0 si empieza como textura
*/
char	compare_to_all_textures(char *line)
{
	char	*set[5];
	int			i;

	define_set(set);
	i = 0;
	while (set[i])
	{
		if (!ft_strncmp(line, set[i], 2))
			return (0);
		i++;
	}
	return (-1);
}
