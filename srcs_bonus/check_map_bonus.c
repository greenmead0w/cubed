/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:26:35 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/20 19:36:04 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

//returns 1 if valid chars, -1 if not and 0 if map == NULL
static int	map_valid_chars(t_vars *vars, char **map)
{
	const char	*valid_chars = "01 NSEWD";
	int			i;
	int			j;

	i = 0;
	if (map == NULL)
		return (-1);
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0' && map[i][j] != '\n')
		{
			if (ft_strchr(valid_chars, map[i][j]) == NULL)
			{
				write(2, CHARACTER, ft_strlen(CHARACTER));
				return (-1);
			}
			if (map[i][j] == 'D')
				vars->door_count++;
			j++;
		}
		i++;
	}
	return (0);
}

//cuenta cantidad de start positions en el mapa
static int	map_start_position(char **map)
{
	int			pos_counter;
	const char	*start_chars = "NSEW";
	int			i;
	int			j;

	pos_counter = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr(start_chars, map[i][j]) != NULL)
				pos_counter++;
			j++;
		}
		i++;
	}
	if (pos_counter != 1)
		write(2, PLAYER, ft_strlen(PLAYER));
	return (pos_counter);
}

/*
**  el mapa no estará sellado (y esta función retornará 1) si:
**  1 - hay un '0' o posición de inicio en el borde del mapa
**  2-  hay un '0' o posición de inicio al lado de un espacio
*/
static int	not_sealed_map(char **map, int lines, int max_len)
{
	int	i;
	int	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n')
			{
				if (i == 0 || i == lines -1 || j == 0 || j == max_len -2)
					return (write(2, WALLS, ft_strlen(WALLS)));
				if (map[i - 1][j - 1] == ' ' || map[i - 1][j] == ' '
					|| map[i - 1][j + 1] == ' ' || map[i][j - 1] == ' '
					|| map[i][j + 1] == ' ' || map[i + 1][j - 1] == ' '
					|| map[i + 1][j] == ' ' || map[i + 1][j + 1] == ' ')
					return (write(2, SPACE, ft_strlen(SPACE)));
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	fill_doors()
{

}

/*
**  suponiendo que:
**  1- no se me pasa como parametro la cantidad de lineas
**  2- no se me pasa como parametro la linea más larga
**  3- caracteres válidos: "0,1, ,N,S,E,W"
**  4- 
*/
int	check_map(t_vars *vars)
{
	char	**rect_map;

	vars->map_cols = map_max_length(vars->map);
	vars->door_count = 0;
	if (map_valid_chars(vars, vars->map) || map_start_position(vars->map) != 1)
		return (-1);
	printf("vars->doors is %d\n", vars->door_count);
	rect_map = make_rectangular_map(vars->map, vars->map_rows, \
		vars->map_cols);
	if (rect_map == NULL)
	{
		write(2, MEM_ALLOC, ft_strlen(MEM_ALLOC));
		return (-1);
	}
	if (not_sealed_map(rect_map, vars->map_rows, vars->map_cols))
	{
		free_double_pointer((void **)rect_map);
		return (-1);
	}
	vars->game_map = rect_map;
	fill_doors();
	return (0);
}
