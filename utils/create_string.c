/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:46:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/14 21:52:14 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

char	*create_string(char **line, int size)
{
	char	*str;
	char	*run;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return ((void *) 0);
	}
	run = str;
	while ('0' <= **line && **line <= '9')
	{
		*run++ = **line;
		(*line)++;
	}
	*run = '\0';
	if (**line == ',')
		(*line)++;
	return (str);
}
