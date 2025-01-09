/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 21:24:20 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/09 20:28:52 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

//CHECKS
# define EMPTY_FILE "The file is empty\n"
# define MEM_ALLOC "Error allocating memory\n"
# define OPEN_FILE "Error opening file\n"
# define WRONG_EXT "File extension is invalid\n"
# define WRONG_FILE "File content not valid\n"
# define ARG_NUM "Wrong argument number\n"

//TEXTURES
# define PATH "The path to the texture does not exist or is incorrect\n"
# define TEXTURES_X_2 "Duplicity in texture\n"

//FLOOR-CEILING COLOR
# define COLOR "Error in floor/ceiling definition\n"
# define COLOR_X_2 "Duplicity in floor/ceiling\n"

//MAP
# define NO_MAP "There is no map\n"
# define WALLS "Open map. Not surrounded by walls\n"
# define CHARACTER "Map contains invalid characters\n"
# define PLAYER "No players or more than one\n"
# define SPACE "Invalid space in map\n"

#endif //ERROR_H
