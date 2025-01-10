/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:28:07 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/10 12:26:59 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include "cubed.h"

size_t			ft_strlen(const char *str);
void			ft_bzero(void *s, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_isalnum(int c);
char			*ft_strcpy(char *dest, char *src);
char			compare_to_all_textures(char *line);
char			cmp_to_one_text(char *line, int i);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlcpy(char *dest, char *src, size_t size);
void			*ft_memset(void *s, int c, size_t n);
int				ft_atoi(const char *str);
void			define_set(char **set);
int				map_max_length(char **map);
int				count_digits_2(char **line);
int				count_digits(char *line);
char			*create_string(char **line, int size);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *src);
char			*get_next_line(int fd);
char			texture_extension(char *line, char *start, int fd);
char			**ft_split(char *s, char c);
t_color			*ft_lstnew(void);
void			ft_lstadd_back(t_color **alst, t_color *new);
void			free_simple_pointer(void *ptr);
void			free_double_pointer(void **ptr);
void			free_mlx(t_conn *conn);
void			free_all_game(t_game *game);
void			free_textures(t_conn *conn, t_texture **ptr, int counter);
void			put_pixel_to_image(t_conn *conn, int x, int y, int color);
int				is_border_map(t_draw_2d *p, t_vars *vars);
int				combine_rgb(t_color *color, char flag);
t_texture		get_ray_texture(t_game *game, t_ray ray);
void			adjusted_wall_height(t_ray *ray,
					t_player *player, t_vars *vars);
void			x_y_wall_rendering_coords(t_ray *ray, t_vars *vars, int i);
double			find_wall_hit_pos(t_ray ray);
unsigned int	get_tex_pixel(t_ray ray, int x, int y);
double			standardize_angle(double angle);

#endif //UTILS_H
