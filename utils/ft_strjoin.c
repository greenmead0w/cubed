/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:11 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/22 18:23:39 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strjoin(char *s1, char *s2)
{
	char	*res;
	char	*run;

	if (!s1 || !s2)
		return (0);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (0);
	run = res;
	while (*s1)
		*run++ = *s1++;
	while (*s2)
		*run++ = *s2++;
	*run = '\0';
	return (res);
}
