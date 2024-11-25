/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:48:56 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 20:22:57 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*result;
	size_t			index;

	result = (unsigned char *) s;
	index = 0;
	while (index < n)
	{
		result[index] = (unsigned char) c;
		index++;
	}
	return ((void *) s);
}
