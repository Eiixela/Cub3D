# **************************************************************************** #
#  #
# :::  ::::::::#
#Makefile   :+:  :+::+:#
# +:+ +:+ +:+  #
#By: aljulien <aljulien@student.42.fr>  +#+  +:+   +#+ #
# +#+#+#+#+#+   +#+#
#Created: 2023/11/10 10:25:02 by aljulien  #+##+#  #
#Updated: 2024/08/13 12:22:31 by aljulien ###   ########.fr#
#  #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJECT_DIR = .obj/

OBJ = $(patsubst %.c,$(OBJECT_DIR)%.o,\
	ft_atoi.c\
	ft_bzero.c\
	ft_isalnum.c\
	ft_isalpha.c\
	ft_isascii.c\
	ft_isdigit.c\
	ft_isprint.c\
	ft_memchr.c\
	ft_memcmp.c\
	ft_memcpy.c\
	ft_memmove.c\
	ft_memset.c\
	ft_strchr.c\
	ft_strlcat.c\
	ft_strlcpy.c\
	ft_strlen.c\
	ft_strncmp.c\
	ft_strnstr.c\
	ft_strrchr.c\
	ft_tolower.c\
	ft_toupper.c\
	ft_calloc.c\
	ft_itoa.c\
	ft_putchar_fd.c\
	ft_putnbr_fd.c\
	ft_putendl_fd.c\
	ft_putstr_fd.c\
	ft_striteri.c\
	ft_strjoin.c\
	ft_strmapi.c\
	ft_strtrim.c\
	ft_strdup.c\
	ft_substr.c\
	ft_split.c\
	ft_strcmp.c\
	ft_dstrlen.c\
	ft_atoll.c\
	ft_free_dtab.c\
	ft_strndup.c\
	ft_strncpy.c)

OBJ_B = $(patsubst %.c,$(OBJECT_DIR)%.o,\
		ft_lstnew_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstclear_bonus.c\
		ft_lstiter_bonus.c\
		ft_lstmap_bonus.c )


DEPENDENCIES = $(OBJ:.o=.d) $(OBJ_B:.o=.d)

NAME = libft.a

.PHONY: all clean fclean re debug run

all: $(NAME)

-include $(DEPENDENCIES)

$(NAME): $(OBJ) $(OBJ_B)
	ar rcs $@ $^

$(OBJECT_DIR)%.o: %.c libft.h | $(OBJECT_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJECT_DIR):
	mkdir -p $(OBJECT_DIR)

clean:
	rm -rf $(OBJECT_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

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