/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_to_one_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:17:45 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/19 19:24:56 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	cmp_to_one_text(char *line, int i)
{
	char	*set[4];

	define_set(set);
	//if (ft_strncmp(line, set[i], 2)); ORIGINAL
	if (!ft_strncmp(line, set[i], 2)) //MODIFICADO, retorna 1 cuando hay match no?
		return (1);
	else
		return (0);
}