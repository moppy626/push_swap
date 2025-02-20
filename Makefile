sudo cc main.c libft/ft_atoi.c libft/ft_isdigit.c
sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 2 1 3 5