/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_extension.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 12:51:03 by mzuloaga          #+#    #+#             */
/*   Updated: 2025/01/23 20:17:00 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <unistd.h>

char	texture_extension(char *line, char *start, int fd)
{
	int	path_len;

	path_len = line - start;
	if (path_len < 4 || ft_strncmp(line - 4, ".xpm", 4) != 0)
	{
		close(fd);
		return (-1);
	}
	return (0);
}
