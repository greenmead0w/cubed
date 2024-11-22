/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:46:24 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 21:10:25 by dpinedo-         ###   ########.fr       */
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
	while ('0' <= **line <= '9')
		*run++ = (*line)++;
	*run = '\0';
	if (**line = ',')
		(*line)++;
	return (str);
}
