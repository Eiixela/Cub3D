# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljulien <aljulien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/25 14:26:21 by aljulien          #+#    #+#              #
#    Updated: 2024/10/01 10:04:50 by aljulien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

INCLUDE_DIR = inc/
LIBFT_DIR = libft/

CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) 
DFLAGS = -MMD -MP
LFLAGS = -L$(LIBFT_DIR) -lft 

OBJECT_DIR = .obj/

OBJECTS = $(patsubst srcs/%.c,$(OBJECT_DIR)%.o,\
		srcs/main.c\
		srcs/parsing/parsing.c\
		srcs/parsing/file_check.c\
		srcs/parsing/init.c\
		srcs/parsing/parsing_utils.c\
		srcs/parsing/cardinal_check.c\
		srcs/parsing/textures_check.c\
		srcs/parsing/color_check.c\
		srcs/gnl/get_next_line.c\
		srcs/gnl/get_next_line_utils.c\
							)

OBJ_SUBDIRS = $(sort $(dir ${OBJECTS}))

DEPENDENCIES = $(OBJECTS:.o=.d)

LIBFT = $(LIBFT_DIR)libft.a

NAME = cub

.PHONY: all
all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJECTS) | $(LIBFT)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ $(OBJECTS) $(LFLAGS)

$(OBJECT_DIR)%.o: srcs/%.c | $(OBJECT_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) $(DFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p ${OBJ_SUBDIRS}

$(LIBFT)::
	@make --no-print-directory -C $(LIBFT_DIR)


.PHONY: clean
clean:
	rm -rf $(OBJECT_DIR)
	@make --no-print-directory -C $(LIBFT_DIR) clean


.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	@make --no-print-directory -C $(LIBFT_DIR) fclean


.PHONY: re
re: fclean
	@make --no-print-directory all

.PHONY: debug
debug:
	@clear
	@make -s re CFLAGS+="-g3 -fsanitize=address"

.PHONY: run
run:
	@clear
	@make -sj re
	@./$(NAME)
