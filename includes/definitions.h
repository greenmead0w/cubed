/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 22:16:56 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/09 22:14:32 by dpinedo-         ###   ########.fr       */
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

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

# define NORTH_W "textures/north.xpm"
# define SOUTH_W "textures/south.xpm"
# define EAST_W "textures/east.xpm"
# define WEST_W "textures/west.xpm"

#endif //DEFINITIONS_H
