#include "push_swap.h"

void	upd_stat(int val, t_status *stat)
{
	if (stat->b_max == 0 || stat->b_max < val)
		stat->b_max = val;
	if (stat->b_min == 0 || stat->b_min > val)
		stat->b_min = val;
}

void	p_src(t_list **from, t_list **to, t_status *stat)
{
	t_list	*temp;

    // if (!*from || *from == *to) 
    //     return;
	upd_stat((*from)->val, stat);
	temp = *from;
	if (*from == (*from)->next)
		*from = NULL;
	else
	{
		(*from)->next->prev = (*from)->prev;
		(*from)->prev->next = (*from)->next;
		*from = (*from)->next;
	}
	if (!*to)
	{
		temp->prev = temp;
		temp->next = temp; 
	}
	else
	{
		temp->prev = (*to)->prev;
		temp->next = *to;
		(*to)->prev->next = temp;
		(*to)->prev = temp;
	}
	*to = temp;
}

/*
	pa・pb処理を実施します
*/
void	p(t_list **a, t_list **b, t_status *stat, char target)
{
	if (target == 'b')
	{
		p_src(a, b, stat);
		stat->a_size--;
	}
	else
	{
		p_src(b, a, stat);
		stat->a_size++;
	}
	ft_printf("p%c\n", target);
}






