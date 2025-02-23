sudo cc main.c libft/ft_atoi.c idou.c
sudo valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./a.out 9 10 5 2 3 8 1 7 4 6
