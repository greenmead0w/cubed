/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinedo- <dpinedo-@student.42urduliz.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:24:20 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/20 19:16:21 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//CHECKS
# define MEM_ALLOC "Error allocating memory\n"
# define OPEN_FILE "Error openning file\n"
# define WRONG_EXT "File extension is invalid\n"
# define WRONG_FILE "File format not valid\n"

//TEXTURES
# define ORIENTATION "Invalid orientation\n"
# define PATH "The path to the texture does not exist or is incorrect\n"
# define TEXTURES_X_2 "Duplicity in floor/ceiling\n"

//FLOOR-CEILING COLOR
# define COLOR "Error in floor/ceiling definition\n"
# define COLOR_X_2 "Duplicity in floor/ceiling\n"

//MAP
# define WALLS "Open map. Not surrended by walls\n"
# define CHARACTER "Map contains invalid characters\n"
# define PLAYER "No players or more than one\n"

#endif //ERROR_H
