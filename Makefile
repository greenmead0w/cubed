# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ithernan <ithernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 01:31:40 by dpinedo-          #+#    #+#              #
#    Updated: 2024/12/03 20:34:38 by dpinedo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs
#SRCS_DIR_BONUS = srcs_bonus
HEADS_DIR = includes
OBJS_DIR = objs
#OBJS_DIR_BONUS = objs
LIBS_DIR = libraries

NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -iquote $(HEADS_DIR)
LDLFLAGS = -Llibraries
RM = -f

SRCS =	main_cubed.c\
	check.c\
	examine_color.c\
	fill_colors_list.c\
	fill_textures_matrix.c\
	parse.c\
	check_map.c\
	examine_line.c\
	fill_map.c

#SRCS_BONUS = main_bonus.c\

LIBS = libutils.a libmlx.a
LIBS_PATH = $(patsubst %.a,$(LIBS_DIR)/%.a,$(LIBS))

LIBS1 = -lutils -lmlx

OBJS = $(SRCS:.c=.o)
OBJS_PATH = $(patsubst %.o,$(OBJS_DIR)/%.o,$(OBJS))

#OBJS_BONUS = $(SRCS_BONUS:.c=.o)
#OBJS_PATH_BONUS = $(patsubst %.o,$(OBJS_DIR_BONUS)/%.o,$(OBJS_BONUS))

vpath %.c $(SRCS_DIR) $(SRCS_DIR_BONUS)
vpath %.o $(OBJS_DIR)
vpath %.a $(LIBS_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS_PATH) $(CPPFLAGS) $(LDLFLAGS) $(LIBS1) -o $@

#bonus: $(OBJS_BONUS) $(LIBS)
#	$(CC) $(CFLAGS) $(OBJS_PATH_BONUS) $(CPPFLAGS) $(LDLFLAGS) $(LIBS1) -o $(BONUS_NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(OBJS_DIR)/$@

libutils.a:
	$(MAKE) -C utils/

clean:
	rm -f $(OBJS_PATH) $(OBJS_PATH_BONUS)
	$(MAKE) -C utils/ clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -f $(LIBS_PATH)

re: fclean all

.PHONY: all clean fclean re
