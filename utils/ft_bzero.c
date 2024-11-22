/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <dpinedo-@42.urduliz.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:48:56 by kali              #+#    #+#             */
/*   Updated: 2024/07/01 15:28:46 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
