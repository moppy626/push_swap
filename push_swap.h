#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

# define UNDER  0
# define OVER 1
# define A 0
# define B 1
# define AB 2

typedef struct s_list{
	struct s_list	*prev;
	int		val;
	struct s_list	*next;
}	t_list;

typedef struct s_data{
	struct s_list	*a;
	ssize_t			a_size;
	struct s_list	*b;
	ssize_t			b_size;
}	t_data;
int	rotate(t_data *data, int mode);
void	swap(t_list **list, int mode);
int	reverse_rotate(t_data *data, int mode);
int	push(t_data *data, int mode);
int find_median(t_list **list, ssize_t size);
t_list	*new_val(int val);
void free_list(t_list **list);
t_list *read_args(int argc, char **argv);
void error(char *msg, t_list **lst, char **splited);
int is_sorted(t_list **list, ssize_t size);
ssize_t get_stack_size(t_list **list);
int	to_int(const char *str, t_list **lst, char **splited);
void free_splited(char **splited);

#endif

