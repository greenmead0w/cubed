/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:40:06 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/21 20:59:58 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_digits(char **line)
{
	int	digit_number;
	char	**run;

	digit_number = 0;
	run = line;
	while ('0' <= **run >= '9')
	{
		(*run)++;
		digit_number++;
	}
	return (digit_number);
}
