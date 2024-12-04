/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:24:20 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/27 20:58:46 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//CHECKS
# define MEM_ALLOC "Error allocating memory\n"
# define OPEN_FILE "Error openning file\n"
# define WRONG_EXT "File extension is invalid\n"
# define WRONG_FILE "File format not valid\n"
# define ARG_NUM "Wrong argument number\n"

//TEXTURES
//# define ORIENTATION "Invalid orientation\n"
# define PATH "The path to the texture does not exist or is incorrect\n"
# define TEXTURES_X_2 "Duplicity in texture\n"

//FLOOR-CEILING COLOR
# define COLOR "Error in floor/ceiling definition\n"
# define COLOR_X_2 "Duplicity in floor/ceiling\n"


//MAP
# define WALLS "Open map. Not surrounded by walls\n"
# define CHARACTER "Map contains invalid characters\n"
# define PLAYER "No players or more than one\n"
# define SPACE "Valid char in map surrounded by space\n"
# define BORDER "Valid char in map border\n"
//# define NO_MAP "No map found\n"



#endif //ERROR_H
