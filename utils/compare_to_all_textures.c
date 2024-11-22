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

char	compare_to_all_textures(char *line)
{
	char	*set[4];

	define_set(set);
	while (*set)
	{
		if (!ft_strncmp(line, *set++, 2))
			return (0);
	}
	return (-1);
}
