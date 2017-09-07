# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihodge <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/08/10 20:14:04 by ihodge            #+#    #+#              #
#    Updated: 2017/09/07 13:55:44 by ihodge           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRCS = main.c \
	   create_lists.c \
	   coords.c \
	   projection.c \
	   draw.c \
	   transformation_matrices.c \
	   bonuses.c \
	   bonuses2.c

FILES = $(addprefix src/, $(SRCS))
OBJFILES = ${SRCS:.c=.o}
LIB = libft/libft.a
MLX = minilibx/libmlx.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJFILES) $(LIB) $(MLX)
	gcc -Wall -Werror -Wextra -framework OpenGL -framework Appkit $(OBJFILES) $(LIB) $(MLX) -o $@

$(LIB): force
	make -C libft

$(MLX): force
	make -C minilibx

%.o: src/%.c
	gcc -Wall -Wextra -Werror -c $< -o $@

force:
	@true

clean:
	rm -f $(OBJFILES)
	make clean -C libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C libft
	make clean -C minilibx

re: fclean all
