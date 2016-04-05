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

NAME1		= ft_nm

NAME2		= ft_otool

SRC1		= ft_nm.c symtype.c

SRC2		= ft_otool.c

OBJ1		= $(SRC1:.c=.o)

OBJ2		= $(SRC2:.c=.o)

CC			= gcc

CFLAGS		= -Werror -Wall -Wextra -g

LIB_LIBFT	= -L libft -lft

INCLUDES	= -I libft/includes

all:	$(NAME1)
		$(NAME2)

$(NAME):
	make -C libft/
	$(CC) $(CFLAGS) -c $(SRC1) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME1) $(OBJ1) $(LIB_LIBFT)
	$(CC) $(CFLAGS) -c $(SRC2) $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME2) $(OBJ2) $(LIB_LIBFT)

clean:
	rm -f $(OBJ1)
	rm -f $(OBJ2)

fclean: clean
	rm -f $(NAME1)
	rm -f $(NAME2)

re: fclean all

.PHONY: all clean fclean re