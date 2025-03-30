
SRC = main.c push.c swap.c find_median.c
SRC_LIBFT = ft_memcpy.c ft_atoi.c 
SRC_PRINTF = str_funcs.c ft_strlen.c printf_funcs.c ft_printf.c

SRC_LIBFT := $(addprefix libft/, $(SRC_LIBFT))
SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))

all: a.out

a.out:$(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
	sudo cc $(SRC) $(SRC_LIBFT) $(SRC_PRINTF)
test:a.out
	sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 29 44 38 12 95 51 81 82 70 71 86 64 6 48 45 54 22 53 14 2 41 37 56 4 63 3 46 94 96 100 59 58 83 47 99 67 25 32 92 66 87 61 26 62 91 55 73 5 69 42 18 76 36 31 20 65 84 13 68 9 89 77 43 97 28 50 34 7 75 10 11 1 78 39 16 90 24 60 33 40 8 19 79 57 88 98 93 15 74 35 85 52 17 80 23 72 21 30 49 27
	