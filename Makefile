# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/19 21:24:23 by mmachida          #+#    #+#              #
#    Updated: 2025/04/19 21:24:23 by mmachida         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror
NAME = push_swap
SRC = main.c push.c swap.c find_median.c set_lists.c check_args.c tools.c
SRC_LIBFT = ft_memcpy.c ft_split.c
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

OBJS = $(SRC:.c=.o) $(SRC_PRINTF:.c=.o) $(SRC_LIBFT:.c=.o)

all: $(NAME)

$(NAME):$(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(NAME) $(OBJS)

re: fclean all

.PHONY: all clean fclean re
