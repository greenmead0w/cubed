/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_functions_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:26:06 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/23 20:24:56 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

t_color	*ft_lstnew(void)
{
	t_color	*new_node;

	new_node = (t_color *) malloc(sizeof(t_color));
	if (new_node != 0)
		ft_bzero(new_node, sizeof(t_color));
	return (new_node);
}

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
