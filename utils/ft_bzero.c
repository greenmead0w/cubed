/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:48:56 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 20:23:47 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*result;
	size_t			index;

	if (n != 0)
	{
		result = (unsigned char *) s;
		index = 0;
		while (index < n)
		{
			result[index] = 0;
			index++;
		}
	}
}
