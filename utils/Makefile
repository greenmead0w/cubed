#**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpinedo- <dpinedo-@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 01:31:40 by dpinedo-          #+#    #+#              #
#    Updated: 2024/11/27 20:22:44 by dpinedo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


HEADS_DIR = ../includes/
NAME = ../libraries/libutils.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -iquote $(HEADS_DIR)
RM = -f

SRCS =  ft_strcmp.c\
	compare_textures_functions.c\
	free_functions.c\
	ft_strlcpy.c\
	ft_atoi.c\
	ft_memset.c\
	ft_strlen.c\
	count_digits.c\
	ft_bzero.c\
	ft_strchr.c\
	ft_strncmp.c\
	create_string.c\
	ft_isalnum.c\
	ft_strcmp.c\
	ft_strdup.c\
	define_textures_set.c\
	ft_strjoin.c\
	gnl.c\
	ft_lstnew.c\
	ft_lstadd_back.c\
	ft_strcpy.c\
	map_max_length.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
