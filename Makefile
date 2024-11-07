# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 14:26:21 by aljulien          #+#    #+#              #
#    Updated: 2024/11/07 16:28:38 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

INCLUDE_DIR = inc/
LIBFT_DIR = libft/
MLX_DIR = mlx/

CFLAGS = -Wall -Wextra -Werror -g3 #-Ofast -march=native -flto -pipe -pg
IFLAGS = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
DFLAGS = -MMD -MP
LFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

OBJECT_DIR = .obj/

OBJECTS = $(patsubst srcs/%.c,$(OBJECT_DIR)%.o,\
		srcs/main.c\
		srcs/free.c\
		srcs/parsing/parsing.c\
		srcs/parsing/file_check.c\
		srcs/parsing/init.c\
		srcs/parsing/parsing_utils.c\
		srcs/parsing/cardinal_check.c\
		srcs/parsing/cardinal_found_all.c\
		srcs/parsing/map_check.c\
		srcs/parsing/flood_fill.c\
		srcs/parsing/map_check_utils.c\
		srcs/parsing/fill_map.c\
		srcs/parsing/fill_map_square.c\
		srcs/parsing/textures_check.c\
		srcs/parsing/check_color.c\
		srcs/parsing/fill_color.c\
		srcs/parsing/free_once_map_square.c\
		srcs/parsing/look_for_color.c\
		srcs/gnl/get_next_line.c\
		srcs/gnl/get_next_line_utils.c\
		srcs/mlx_init/mlx_init.c\
		srcs/mlx_init/handle_events.c\
		srcs/mlx_init/player_movement.c\
		srcs/mlx_init/key_directions.c\
		srcs/mlx_init/textures.c\
		srcs/draw/big_init.c\
		srcs/draw/draw_rays.c\
		srcs/draw/draw_map2d.c\
		srcs/draw/draw_rays_utils.c\
		srcs/draw/draw_ceiling_floor.c\
		srcs/draw/draw.c\
		srcs/draw/ray_casting.c\
							)

OBJ_SUBDIRS = $(sort $(dir ${OBJECTS}))

DEPENDENCIES = $(OBJECTS:.o=.d)

LIBFT = $(LIBFT_DIR)libft.a
MLX = $(MLX_DIR)libmlx.a
NAME = cub3D

.PHONY: all
all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS) | $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

$(OBJECT_DIR)%.o: srcs/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p ${OBJ_SUBDIRS}

$(LIBFT)::
	@make --no-print-directory -C $(LIBFT_DIR)

$(MLX)::
	@make --no-print-directory -C $(MLX_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean
	@make --no-print-directory -C $(MLX_DIR) clean

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean
	@make --no-print-directory -C $(MLX_DIR) clean

.PHONY: re
re: fclean
	@make --no-print-directory all

.PHONY: debug
debug:
	@clear
	@make -s re CFLAGS+="-g3 -fsanitize=address"
	@./$(NAME)

.PHONY: run
run:
	@clear
	@make -sj re
	@./$(NAME)
