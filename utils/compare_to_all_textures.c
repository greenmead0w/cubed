/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 21:37:19 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/18 22:16:23 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
** retorna 0 si empieza como textura
*/
char	compare_to_all_textures(char *line)
{
	char	*set[4];
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
