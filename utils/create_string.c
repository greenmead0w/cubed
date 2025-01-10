/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:46:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:43:10 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*create_string(char **line, int size)
{
	char	*str;
	char	*run;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return ((void *) 0);
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
