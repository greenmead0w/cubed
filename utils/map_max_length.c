/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_max_length.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:27:44 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 22:21:25 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int map_max_length(char **map)
{
	int temp;
	int len;
	int i;

	temp = 0;
	len = 0;
	i = 0;
	while(map[i] != NULL)
	{
		temp = ft_strlen(map[i]);
		if (temp > len)
            		len = temp;
		i++;
	}
	return (len);
}
