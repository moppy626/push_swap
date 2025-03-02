
SRC = main.c push.c swap.c
SRC_LIBFT = ft_memcpy.c ft_atoi.c 
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

all: a.out

a.out:$(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
	sudo cc $(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
test:a.out
	sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 9 10 5 2 3 8 1 7 4 6
