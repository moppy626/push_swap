
SRC = main.c push.c swap.c find_median.c set_lists.c check_args.c tools.c
SRC_LIBFT = ft_memcpy.c ft_split.c
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

all: push_swap

push_swap:$(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
	sudo cc $(SRC) $(SRC_LIBFT) $(SRC_PRINTF) -o push_swap
# test:push_swap
# 	sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./push_swap  "48 45 43 6 7 37 2 41 50 28 15 31 39 24 32 42 21 16 27 44 23 38 49 34 19 1 8 47 29 9 17 26 3 10 14 35 4 12 33 18 40 22 20 36 13 11 46 30 25 5"
test:push_swap
	python3 push_swap_tester.py -l 100