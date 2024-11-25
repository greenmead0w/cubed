/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:00:37 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/22 18:48:25 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_lstadd_back(t_color **alst, t_color *new)
{
	t_color	*running_node;

	if (new != 0)
	{
		if (*alst != 0)
		{
			running_node = *alst;
			while (running_node -> next != 0)
				running_node = running_node -> next;
			running_node -> next = new;
		}
		else
			*alst = new;
	}
}
