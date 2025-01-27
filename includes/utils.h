/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:28:07 by dpinedo-          #+#    #+#             */
/*   Updated: 2025/01/27 19:54:47 by dpinedo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>

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
double			standardize_angle(double angle);

#endif //UTILS_H
