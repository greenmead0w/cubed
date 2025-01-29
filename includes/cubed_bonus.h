/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:31:54 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/28 21:29:05 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_BONUS_H
# define CUBED_BONUS_H

# include "structs_bonus.h" 
# include "error.h"
# include "utils.h"
# include "definitions.h"
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <sys/time.h>
# include "../minilibx-linux/mlx.h"

char	check(char *file, t_game *game, t_track_items *track_elements);
int	check_doors(char **map);
char	examine_line(char *line, t_game *game, t_track_items *track_elems);
char	examine_color(char *line, t_track_items *track_elements);
char	parse(char *file, t_game *game);
char	fill_colors_list(char *line, t_game *game);
char    fill_walls_matrix(char *line, t_vars *vars);
char	fill_map(t_vars *vars, char *line);
char	**make_rectangular_map(char **map, int lines, int max_len);
int		check_map(t_vars *vars);
char	execute(t_game *game);
void	*create_connection(t_game *game);
int     init_game(t_game *game);
char	init_images(t_game *game);
char	get_textures(t_conn *con, t_vars *vars);
void    init_textures(t_texture **tex, t_texture **type, enum e_mode mode);
void	render_map(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int kc, t_game *game);
int		initial_player_data(char **map, int rows,
			int columns, t_player *player);
int		ft_close_conn(t_game *game);
void	central_ray_cast(t_ray *ray, t_player *player, t_vars *vars);
void	update(t_game *game);
void	draw_2d_map(t_game *game);
void	draw_player(t_conn *conn, t_player *player, t_vars *vars);
int		is_collision(double x, double y, t_player *player, t_vars *vars);
int		ray_is_wall(int x, int y, t_vars *vars, t_ray *ray);
int		pos_is_wall(double x, double y, t_vars *vars);
void	vertical_border(t_ray *ray, t_player *player, t_vars *vars);
void	horizontal_border(t_ray *ray, t_player *player, t_vars *vars);
void	draw_all_rays(t_game *game);
void	draw_ray_cast(t_game *game, int i);
void	draw_ceiling(t_game *game);
void	draw_floor(t_game *game);
void	set_texture_to_display(t_vars *vars);

t_color			*ft_lstnew(void);
void			ft_lstadd_back(t_color **alst, t_color *new);
void			free_simple_pointer(void *ptr);
void			free_double_pointer(void **ptr);
void			free_mlx(t_conn *conn);
void			free_all_game(t_game *game);
void			free_images(t_conn *conn, t_texture **ptr, int counter, int flag_walls);
void			put_pixel_to_image(t_conn *conn, int x, int y, int color);
int				is_border_map(t_draw_2d *p, t_vars *vars);
int				combine_rgb(t_color *color, char flag);
t_texture		get_ray_texture(t_game *game, t_ray ray);
void			adjusted_wall_height(t_ray *ray, t_player *player, t_vars *vars);
void			x_y_wall_rendering_coords(t_ray *ray, t_vars *vars, int i);
double			find_wall_hit_pos(t_ray ray);
unsigned int	get_tex_pixel(t_ray ray, int x, int y);
int		mouse_press(int key_code, int x, int y, t_game *game);
int		mouse_release(int key_code, int x, int y, t_game *game);
void	draw_health(t_game *game);


#endif //CUBED_BONUS_H
