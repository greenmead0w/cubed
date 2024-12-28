/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:26:50 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/26 18:10:31 by mzuloaga         ###   ########.fr       */
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

//buffer to dump pixels to window
typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_image;

//Connection
typedef struct s_conn
{
	void	*mlx;
	void	*win;
	t_image	image;
}		t_conn;

typedef struct s_vars
{
	void	*textures[5];
	char	**map;
	char	**game_map; //rect map
	int	map_rows;
	int	map_cols;
	int screen_width;
	int screen_height;
	int num_rays;
}		t_vars;

//player data 
typedef struct s_player 
{
	int turn_direction; // 0 default, +1 right, -1 left
	char walk_direction; // '0' default, 'w', 'a', 's', 'd'
	double rotation_angle; //where is the player looking at, in radians
	double rotation_speed; //how many radians will the player rotate per frame / key_press
	double speed; //how many pixels per frame / key press will player move in total (hypotenuse)
	double	play_pos[2]; //player position in the map (tile based, not pixel based)
	double dist_to_plane; //distance to projection plane, constant
	double field_of_view;  
}	t_player;

// typedef struct s_plane
// {
// 	int screen_width;
// 	int screen_height;

 	
// } t_plane;


typedef struct s_ray 
{
	double angle; 
	double distance; //rays distance to the wall
	double point_a[2]; //(x, y) for point A

} t_ray;

//General struct for the game
typedef struct s_game
{
	t_color	*color_root;
	t_vars	*vars;
	t_conn	*conn;
	t_player *player;
	t_ray *rays;
	int update; //"dirty flag", signals if image should be updated (1), else 0

}		t_game;

#endif //STRUCTS_H
