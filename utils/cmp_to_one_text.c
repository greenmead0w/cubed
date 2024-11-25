/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp_to_one_text.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:17:45 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 20:15:00 by mzuloaga         ###   ########.fr       */
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
