/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:22:12 by kali              #+#    #+#             */
/*   Updated: 2024/11/25 20:12:48 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

t_color	*ft_lstnew(void)
{
	t_color	*new_node;

	new_node = (t_color *) malloc(sizeof(t_color));
	if (new_node != 0)
		ft_bzero(new_node, sizeof(t_color));
	return (new_node);
}
