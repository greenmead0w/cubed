/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:26:50 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 21:25:46 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

//Checks
typedef struct s_track_items
{
	char	colors_ok[3];
	char	textures_ok[5];
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

//Connection
typedef struct s_conn
{
	void	*mlx;
	void	*win;
}		t_conn;

typedef struct s_vars
{
	void	*textures[5];
	char	**map;
	char	**game_map;
	int	map_rows;
	int	map_cols;
	int turn_direction; // 0 default, -1 right, +1 left
	int walk_direction; // 0 default, -1 backwards, +1 front
	double rotation_angle; //where is the player looking at, in radians
	double rotation_speed; //how many radians will the player rotate per frame / key_press
	int move_speed; //how many pixels per frame / key press will player move
	int	play_pos[2];
}		t_vars;

//General struct for the game
typedef struct s_game
{
	t_color	*color_root;
	t_vars	*vars;
	t_conn	*conn;
}		t_game;

#endif //STRUCTS_H
