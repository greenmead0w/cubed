/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:28:07 by dpinedo-          #+#    #+#             */
/*   Updated: 2024/11/25 20:36:22 by mzuloaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>
#include "structs.h"

size_t	ft_strlen(const char *str);
void	ft_bzero(void *s, size_t n);
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_isalnum(int c);
char	*ft_strcpy(char *dest, char *src);
char	compare_to_all_textures(char *line);
char    cmp_to_one_text(char *line, int i);
char    *ft_strchr(const char *s, int c);
size_t  ft_strlcpy(char *dest, char *src, size_t size);
void    *ft_memset(void *s, int c, size_t n);
int	ft_atoi(const char *str);
void	define_set(char **set);
int	map_max_length(char **map);
int	count_digits_2(char **line);
int	count_digits(char *line);
char	*create_string(char **line, int size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *src);
char	*get_next_line(int fd);


t_color	*ft_lstnew(void);
void	ft_lstadd_back(t_color **alst, t_color *new);

void	free_simple_pointer(void *ptr);
void	free_double_pointer(void **ptr);
void	free_all_game(t_game *game);

#endif //UTILS_H
