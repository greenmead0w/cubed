/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:31:54 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/10 20:43:27 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "structs.h" 
# include "error.h"
# include "utils.h"
# include "definitions.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
#include "../minilibx-linux/mlx.h"

char    check(char *file, t_game *game, t_track_items *track_elements);
char    examine_line(char *line, t_game *game, t_track_items *track_elems);
char    examine_color(char *line, t_track_items *track_elements);
char    parse(char *file, t_game *game);
char    fill_colors_list(char *line, t_game *game);
char    fill_textures_matrix(char *line, t_vars *vars);
char    fill_map(t_vars *vars, char *line);
int	check_map(t_vars *vars);
char    execute(t_game *game);
void	get_textures(t_conn *con, void **textures);
void	load_background(t_game *game);
int     key_hook(int keycode, t_game *game);
int	find_play_pos(char **map, int rows, int columns, int *player_pos);
int     ft_close_conn(t_vars *vars);

#endif //CUBED_H
