/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:26:50 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/20 18:56:01 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/types.h>

//Checks
typedef struct s_track_items
{
	char	colors_ok[3];
	char	textures_ok[5];
	int		item_counter; // 2 colors + 4textures --> 6. if not 6, .cub is wrong
	char	map_flag; //if == 1 then primera linea del mapa leída, por lo que
					//todas las demas lineas hasta EOF son de mapa
}		t_track_items;

//Colors for ceiling, floor
typedef struct s_color
{
	char			cf;
	int				r_color;
	int				g_color;
	int				b_color;
	struct s_color	*next;
}		t_color;

//buffer to dump pixels to window
typedef struct s_image
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}		t_image;

//Connection
typedef struct s_conn
{
	void	*mlx;
	void	*win;
	t_image	image;
}		t_conn;

//used for the 2d map rendering because norminette constraints
typedef struct s_draw_2d
{
	int		curr_x;
	int		curr_y;
	int		start_x;
	int		start_y;
	char	value;
}	t_draw_2d;

typedef struct s_textures
{
	t_image	img;
	int		width;
	int		height;
	char	*path;
	char	side; //which side of the wall texture corresponds to
}		t_texture;

typedef struct s_vars
{
	t_texture	*textures[4];
	char		**map;
	char		**game_map; //rect map
	int			map_rows;
	int			map_cols;
	int			screen_width;
	int			screen_height;
	int			num_rays;
	int			big_tile;
	int			min_tile;
}		t_vars;

//player data 
typedef struct s_player
{
	int		turn_direction; // 0 default, +1 right, -1 left
	char	walk_direction; // '0' default, 'w', 'a', 's', 'd'
	double	rotation_angle; //where the player is looking at, in radians
	double	rotation_speed; //how many radians will player rotate per keyPress
	double	speed; //pixels per keyPress player will move in total (hypotenuse)
	double	play_pos[2]; //player position in map (tile based, not pixel based)
	double	dist_to_plane; //distance to projection plane, constant
	double	field_of_view;
	double	display_size; //size (pixels) of the player figure in the 2d miniMap
}		t_player;

typedef struct s_ray
{
	double		angle;
	double		distance; //rays distance to the wall
	double		pos[2];//XY values for intersections (2d grid, not pixel based)
	char		hit_side; //the side of the wall that the ray has hit
	char		border; //'H' if ray hit horz intersection, 'V' if vert
	double		wall_height; //based on the adjusted ray distace to the wall
	int			x;//pixel coord values where wall will be rendered
	int			y; // (pixel) starting position for the wall strip
	t_texture	tex; //texture that this ray has summoned
}		t_ray;

typedef struct s_delay
{
	time_t	delay_1;
	time_t	delay_2;
	time_t	delay_3;
	time_t	delay_4;
}	t_delay;

//General struct for the game
typedef struct s_game
{
	t_color		*color_root;
	t_vars		*vars;
	t_conn		*conn;
	t_player	*player;
	t_ray		*rays;
	int			update; //"dirty flag", 1 if image should be updated, else 0
	t_delay		*delays;
}	t_game;

#endif //STRUCTS_H
