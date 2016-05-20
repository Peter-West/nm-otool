#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppellegr <ppellegr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/04/23 20:58:17 by ppellegr          #+#    #+#              #
#    Updated: 2014/04/23 20:58:18 by ppellegr         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME1 := ft_nm

# NAME2 := ft_otool

SRC1 := ft_nm.c symtype.c symlist.c print.c sort.c handle_archive.c

# SRC2 := ft_otool.c

CC := clang

CFLAGS := -Werror -Wall -Wextra -g

LIB_LIBFT := libft/libft.a

INCLUDES := -I libft/includes

OBJ1 := $(SRC1:.c=.o)

OBJ2 := $(SRC2:.c=.o)

all: $(NAME1)

build:
	make -C libft/

$(NAME1):
	$(CC) $(CFLAGS) -c $(SRC1) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1) $(LIB_LIBFT)

# $(NAME2):
# 	$(CC) $(CFLAGS) -c $(SRC2) $(INCLUDES)
# 	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2) $(LIB_LIBFT)

clean:
	rm -rf $(OBJ1)
	# rm -rf $(OBJ2)

fclean: clean
	rm -rf $(NAME1)
	# rm -rf $(NAME2)

re: fclean all

.PHONY: all clean fclean re