# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzuloaga <mzuloaga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/15 01:31:40 by dpinedo-          #+#    #+#              #
#    Updated: 2025/01/28 21:30:46 by dpinedo-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_DIR = srcs
SRCS_DIR_BONUS = srcs_bonus
HEADS_DIR = includes
OBJS_DIR = objs
OBJS_DIR_BONUS = objs
LIBS_DIR = libraries
MLX_DIR = minilibx-linux

NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = cc
CFLAGS = -Wall -Wextra -Werror -D SPEED=1 -D USAIN=2
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
	init_game.c\
	execute.c\
	open_connection.c\
	update.c\
	display.c\
	mini_map.c\
	mini_map_rays.c\
	vertical_border.c\
	horizontal_border.c\
	update2.c\
	draw_3d.c\
	draw_others.c\
	free_functions2.c\
	free_functions.c\
	ft_list_functions.c

SRCS_BONUS = main_cubed_bonus.c\
	check_bonus.c\
	check_doors_bonus.c\
	examine_color_bonus.c\
	fill_colors_list_bonus.c\
	fill_walls_matrix_bonus.c\
	parse_bonus.c\
	examine_line_bonus.c\
	fill_map_bonus.c\
	make_rectangular_map_bonus.c\
	check_map_bonus.c\
	get_textures_bonus.c\
	events_bonus.c\
	initial_player_data_bonus.c\
	init_game_bonus.c\
	init_images_bonus.c\
	ft_close_conn_bonus.c\
	execute_bonus.c\
	open_connection_bonus.c\
	central_ray_cast_bonus.c\
	update_bonus.c\
	display_bonus.c\
	mini_map_bonus.c\
	mini_map_rays_bonus.c\
	vertical_border_bonus.c\
	horizontal_border_bonus.c\
	update2_bonus.c\
	draw_health_bonus.c\
	animate_sprite_bonus.c\
	draw_3d_bonus.c\
	draw_others_bonus.c\
	free_functions2_bonus.c\
	free_functions_bonus.c\
	ft_list_functions_bonus.c


LIBS =  libmlx.a libutils.a
LIBS_PATH = $(patsubst %.a,$(LIBS_DIR)/%.a,$(LIBS))
LIBS1 = -lutils -lmlx -lXext -lX11 -lm

OBJS = $(SRCS:.c=.o)
OBJS_PATH = $(patsubst %.o,$(OBJS_DIR)/%.o,$(OBJS))

OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS_PATH_BONUS = $(patsubst %.o,$(OBJS_DIR_BONUS)/%.o,$(OBJS_BONUS))

vpath %.c $(SRCS_DIR) $(SRCS_DIR_BONUS)
vpath %.o $(OBJS_DIR)
vpath %.a $(LIBS_DIR) $(MLX_DIR)

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS_PATH) $(CPPFLAGS) $(LDLFLAGS) $(LIBS1) -o $@

bonus: $(OBJS_BONUS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS_PATH_BONUS) $(CPPFLAGS) $(LDLFLAGS) $(LIBS1) -o $(BONUS_NAME)

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
