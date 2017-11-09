#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddufour <ddufour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/24 17:19:40 by ddufour           #+#    #+#              #
#    Updated: 2017/04/14 11:09:31 by ddufour          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Werror -Wextra

SRC =	ft_atoi.c \
		ft_bzero.c \
		ft_putendl.c \
		ft_strlen.c \
		ft_putnbr.c \
		ft_putnbrendl.c \
		ft_isdigit.c \
		ft_putstr.c \
		ft_memalloc.c \
		ft_strsplit.c \
		ft_putchar.c \
		ft_free_tab.c \
		ft_read_file.c \
		ft_strjoinfree.c \
		ft_strnew.c \
		ft_strcpy.c \
		ft_strcat.c \
		ft_memcpy.c \
		iswall.c \
		checkisdigit.c \
		ft_exit.c \
		ft_itoa.c \
		get_alpha.c

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all : $(NAME)

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all