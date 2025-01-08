/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:16:56 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/08 18:35:54 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define BUFFER_SIZE 40
# define INT_MAX 2147483647
# define EPSILON 0.000001

# define XPM_TO_IMAGE mlx_xpm_file_to_image
# define IMAGE_TO_WINDOW mlx_put_image_to_window

# define COLORS_NUM 2
# define TEXTURES_NUM 4
# define SET "FC"
# define SET_2 "NSEW"

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define NORTH_W "textures/bricks.xpm"
# define SOUTH_W "textures/sand.xpm"
# define EAST_W "textures/woolsnow.xpm"
# define WEST_W "textures/ice.xpm"
//# define SPACE_W "textures/space.xpm"

//source: keysym def for XSERVER: 
//	https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h 
//keycode is local to hardware or OS, 
//keysym is global to all devices using XProtocol / XSERVER
# define XK_LEFT 0xff51
# define XK_RIGHT 0xff53
# define XK_W 0x0077
# define XK_A 0x0061
# define XK_S 0x0073
# define XK_D 0x0064
# define XK_ESCAPE 0xff1b

# define TILE_SIZE 64
# define MINI_TILE 16 //minimap tile size
# define RAY_WIDTH 1 //width in pixels of "each ray"

#endif //DEFINITIONS_H
