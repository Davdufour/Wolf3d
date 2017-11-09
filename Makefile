#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/12 17:05:44 by ddufour           #+#    #+#              #
#    Updated: 2017/10/17 14:49:03 by ddufour          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = Wolf3d

RM = rm -f

CC = gcc

CFLAGS = #-Wall -Werror -Wextra

LIBS = -LLibs/libft/ -LLibs/minilibx_macos/

SRCS =	srcs/main.c \
		srcs/parsing.c \
		srcs/raycasting.c \
		srcs/moving.c \
		srcs/ptrfonc.c \
		srcs/useless.c \
		srcs/draw.c \
		srcs/event.c

OBJ = $(SRCS:.c=.o)

$(NAME) : $(OBJ)
	@make -s -C libs/libft
	@echo "Libft Compiled"
	@make -s -C libs/minilibx_macos
	@echo "Minilibx Compiled"
	@$(CC) $(LIBS) -lft -lmlx -framework OpenGL -framework AppKit -lncurses -o $@ $^
	@echo "Wolf3d Compiled"

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@make clean -s -C libs/libft
	@echo ".o Libft delete"
	@make clean -s -C libs/minilibx_macos
	@echo ".o Minilibx delete"
	@$(RM) $(OBJ)
	@echo ".o Wolf3d delete"

fclean : clean
	@$(RM) libs/libft/libft.a
	@echo "libft.a delete"
	@$(RM) libs/minilibx_macos/libmlx.a
	@echo "libmlx.a delete"
	@$(RM) $(NAME)
	@echo "Wolf3d delete"

re : fclean all

#db :
#	@echo "backup delete :"
#	@find . -type f -name "*~" -print -delete -o -type f -name "#*#" -print -delete