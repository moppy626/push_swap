
SRC = main.c push.c swap.c find_median.c set_lists.c
SRC_LIBFT = ft_memcpy.c ft_atoi.c 
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

all: a.out

a.out:$(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
	sudo cc $(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
test:a.out
	sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 6 8 5 9 7 0 1 2 3 4
	