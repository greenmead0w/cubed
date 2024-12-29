/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:31:54 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/12/27 12:38:08 by mzuloaga         ###   ########.fr       */
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
# include <math.h>
# include "../minilibx-linux/mlx.h"

char    check(char *file, t_game *game, t_track_items *track_elements);
char    examine_line(char *line, t_game *game, t_track_items *track_elems);
char    examine_color(char *line, t_track_items *track_elements);
char    parse(char *file, t_game *game);
char    fill_colors_list(char *line, t_game *game);
char    fill_textures_matrix(char *line, t_vars *vars);
char    fill_map(t_vars *vars, char *line);
int		check_map(t_vars *vars);
char    execute(t_game *game);
void	get_textures(t_conn *con, void **textures);
void	render_map(t_game *game);
int     key_press(int keycode, t_game *game);
int     key_release(int kc, t_game *game);
int		initial_player_data(char **map, int rows, int columns, t_player *player);
int     ft_close_conn(t_game *game);
void	update(t_game *game);
void	draw_2d_map(t_game *game);
void	draw_player(t_conn *conn, t_player *player);
void draw_direction_line(t_conn *conn, t_player *player);
int is_wall(int x, int y, t_vars *vars, t_ray *ray);
void vertical_border(t_ray *ray, t_player *player, char **map);
void horizontal_border(t_ray *ray, t_player *player, char **map);

#endif //CUBED_H
