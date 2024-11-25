/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 20:00:37 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 20:26:20 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

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
