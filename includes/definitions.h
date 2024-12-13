/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:16:56 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 21:33:55 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define BUFFER_SIZE 40

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

# define NORTH_W "textures/north.xpm"
# define SOUTH_W "textures/south.xpm"
# define EAST_W "textures/east.xpm"
# define WEST_W "textures/west.xpm"

//source: keysym def for XSERVER: https://www.cl.cam.ac.uk/~mgk25/ucs/keysymdef.h 
//keycode is local to hardware or OS, keysym is global to all devices using XProtocol / XSERVER
#define XK_Left                          0xff51 // left arrow
#define XK_Right                         0xff53  // right arrow
#define XK_w                             0x0077
#define XK_a                             0x0061
#define XK_s                            0x0073
#define XK_d                             0x0064
#define XK_Escape                        0xff1b

#endif //DEFINITIONS_H
