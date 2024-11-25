/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 08:59:33 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 18:27:31 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_get_num_in_base(int *digits, unsigned int size, \
		unsigned int base)
{
	int	power;
	int	index;
	int	nbr;

	power = 1;
	index = size;
	nbr = 0;
	while (index > 0)
	{
		nbr += digits[--index] * power;
		power *= base;
	}
	return (nbr);
}

static int	ft_isspace(int c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || \
			c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	digits[11];
	int	nbr;
	int	index;

	nbr = 1;
	index = 0;
	while (ft_isspace(*str) == 1)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			nbr = -nbr;
		str++;
	}
	while (*str == '0')
		str++;
	while ('0' <= *str && *str <= '9')
		digits[index++] = *str++ - '0';
	if (index != 0)
		nbr = nbr * ft_get_num_in_base(digits, index, 10);
	else
		nbr = 0;
	return (nbr);
}

