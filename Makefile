# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 01:31:40 by dpinedo-          #+#    #+#              #
#    Updated: 2025/01/15 21:02:19 by dpinedo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs
#SRCS_DIR_BONUS = srcs_bonus
HEADS_DIR = includes
OBJS_DIR = objs
#OBJS_DIR_BONUS = objs
LIBS_DIR = libraries
MLX_DIR = minilibx-linux

NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -D SPEED=0
CPPFLAGS = -iquote $(HEADS_DIR) -I$(MLX_DIR)
LDLFLAGS = -L$(LIBS_DIR) -L$(MLX_DIR)
RM = -f

SRCS =	main_cubed.c\
	check.c\
	examine_color.c\
	fill_colors_list.c\
	fill_textures_matrix.c\
	parse.c\
	examine_line.c\
	fill_map.c\
	make_rectangular_map.c\
	check_map.c\
	get_textures.c\
	key_hook.c\
	initial_player_data.c\
	ft_close_conn.c\
	execute.c\
	open_connection.c\
	update.c\
	display.c\
	mini_map.c\
	mini_map_rays.c\
	vertical_border.c\
	horizontal_border.c\
	update2.c


LIBS =  libmlx.a libutils.a
LIBS_PATH = $(patsubst %.a,$(LIBS_DIR)/%.a,$(LIBS))
LIBS1 = -lutils -lmlx -lXext -lX11 -lm

OBJS = $(SRCS:.c=.o)
OBJS_PATH = $(patsubst %.o,$(OBJS_DIR)/%.o,$(OBJS))

vpath %.c $(SRCS_DIR) $(SRCS_DIR_BONUS)
vpath %.o $(OBJS_DIR)
vpath %.a $(LIBS_DIR) $(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS_PATH) $(CPPFLAGS) $(LDLFLAGS) $(LIBS1) -o $@

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $(OBJS_DIR)/$@

libutils.a:
	$(MAKE) -C utils/

libmlx.a:
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS_PATH) $(OBJS_PATH_BONUS)
	$(MAKE) -C utils/ clean
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)
	rm -f $(LIBS_PATH)

re: fclean all

.PHONY: all clean fclean re
