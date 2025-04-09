
SRC = main.c push.c swap.c find_median.c set_lists.c
SRC_LIBFT = ft_memcpy.c ft_atoi.c 
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

all: push_swap

push_swap:$(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
	sudo cc $(SRC) $(SRC_LIBFT) $(SRC_PRINTF) -o push_swap
test:push_swap
	sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./push_swap  10 4 8 6 3 2 9 7 1 5