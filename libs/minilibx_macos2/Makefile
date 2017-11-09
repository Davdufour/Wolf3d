# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gubourge <gubourge@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/24 16:32:16 by gubourge          #+#    #+#              #
#    Updated: 2017/09/25 16:43:31 by gubourge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NOM = libmlx.a

SRC =	mlx_shaders.c \
		mlx_new_window.m \
		mlx_init_loop.m \
		mlx_new_image.m \
		mlx_xpm.c \
		mlx_int_str_to_wordtab.c

OBJ1 = $(SRC:.c=.o)

OBJ = $(OBJ1:.m=.o)


$(NOM):	$(OBJ)
	@ar rc $(NOM) $(OBJ)
	@ranlib $(NOM)

all: $(NOM)

%.o: %.c
	@cc -O2 -o $@ -c $?

%.o: %.m
	@cc -O2 -o $@ -c $?

clean:
	rm -f $(NOM) $(OBJ)
	rm -f mlx_app

fclean : clean
	rm -f $(NOM)

re: fclean all