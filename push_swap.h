#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

typedef struct s_list{
	struct s_list	*prev;
	int		val;
	struct s_list	*next;
}	t_list;
typedef struct s_status{
	int		b_max;
	int		b_min;
	ssize_t	a_size;
}	t_status;

void	s(t_list **list, char target);
void	p(t_list **a, t_list **b, t_status *stat, char target);
void	r(t_list **list, char target);
void	rr(t_list **list, char target);
void	rrr(t_list **a, t_list **b);

#endif

