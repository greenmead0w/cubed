/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <dpinedo-@42.urduliz.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:48:56 by kali              #+#    #+#             */
/*   Updated: 2024/11/20 21:37:42 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
