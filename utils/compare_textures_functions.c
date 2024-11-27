/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_to_all_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:37:19 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/27 20:19:02 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	cmp_to_one_text(char *line, int i)
{
	char	*set[4];

	define_set(set);
	if (!ft_strncmp(line, set[i], 2))
		return (1);
	else
		return (0);
}

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
