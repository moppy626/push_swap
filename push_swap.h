#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

# define UP	  0
# define DOWN 1

typedef struct s_list{
	struct s_list	*prev;
	int		val;
	struct s_list	*next;
}	t_list;

typedef struct s_data{
	struct s_list	*a;
	int				a_size;
	struct s_list	*b;
	int				b_size;
}	t_data;
void	r(t_list **list);
void	s(t_list **list);
void	rr(t_list **list);
void	rrr(t_list **a, t_list **b);
void	p(t_list **from, t_list **to);
#endif

