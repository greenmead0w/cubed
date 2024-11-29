/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 18:01:39 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/29 18:14:36 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	check_map_borders(char **map)
{
	while (*map)
	{
		
		while (**map)
		{
			if (**map == 'F')
			{
				write(2, MAP_OPEN, ft_strlen(MAP_OPEN));
				return (-1);
			}
			(*map)++;
		}
	

char	check_if_map_close(char **map)
{
	where_is_player(map);
	flood_fill(map);
	check_borders(map);
	return (0);
}
