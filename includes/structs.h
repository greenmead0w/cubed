/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:26:50 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 17:59:15 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Checks
typedef struct s_track_items
{
	char	colors_ok[2];
	char	textures_ok[4];
	int	item_counter; // 2 colors + 4textures  --> 6. if not 6, .cub is wrong
	char	map_flag; //map_flag 1 quiere decir que ya se ha leido la primera linea del mapa, 
								// por lo que todas las demas lineas hasta EOF corresponden a la parte del mapa
}		t_track_items;

//Colors for ceiling, floor
typedef struct s_color
{
	char		cf;
	int		r_color;
	int		g_color;
	int		b_color;
	struct s_color	*next;
}		t_color;

//General struct for the game
typedef struct s_game
{
	char	*textures[5];
	t_color	*color_root;
	char	**map;
	char	**game_map;
	int	map_rows_counter;
}		t_game;

#endif //STRUCTS_H
