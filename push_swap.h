#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

typedef struct s_list{
	struct s_list	*prev;
	int		val;
	struct s_list	*next;
}	t_list;

void	s(t_list **list);
void	p(t_list **from, t_list **to);
void	r(t_list **list);
void	rr(t_list **list);

#endif

