/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:16:56 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/16 20:33:19 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define BUFFER_SIZE 40
# define INT_MAX 2147483647
# define EPSILON 0.000001

# define XPM_TO_IMAGE mlx_xpm_file_to_image
//# define IMAGE_TO_WINDOW mlx_put_image_to_window

# define COLORS_NUM 2
# define TEXTURES_NUM 4
# define SET "FC"
# define SET_2 "NSEW"

//execute.c render_game
# ifndef SPEED
#  define SPEED 0
# endif //SPEED

//update.c new_pos
# ifndef USAIN
#  define USAIN 1
# endif //USAIN

//doors textures path - MODIFY FOR ACTUAL DOOR TEXTURES
# define DOOR_OPEN "textures/north.xpm"
# define DOOR_CLOSE "textures/south.xpm"

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

# define MAX_SCREEN_WIDTH 3712 //58 cols
# define MAX_SCREEN_HEIGHT 1920 //32 lines size 64 pixels

# define TILE_SIZE 64
# define MINI_TILE 16 //minimap tile size
# define RAY_WIDTH 1 //width in pixels of "each ray"

# define DAMAGE 5

#endif //DEFINITIONS_H
