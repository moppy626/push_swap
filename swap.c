#include "push_swap.h"

/*
	ra・rb処理を実施します
*/
int	r(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return (0);
	temp = (*list)->next;
	*list = temp;

	return (1);
}
int	rotate(t_data *data, int mode)
{
	if (mode == A)
	{
		ft_printf("ra\n");
		return (r(&data->a));
	}
	else if (mode == B)
	{
		ft_printf("rb\n");
		return (r(&data->b));
	}
	else
	{
		ft_printf("rr\n");
		r(&data->a);
		r(&data->b);
	}
	return (0);
}

/*
	sa・sb処理を実施します
*/
void	swap(t_list **list, int mode)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	if (mode == A)
		ft_printf("sa\n");
	else
		ft_printf("sb\n");
	temp = (*list)->next;
	if (temp->next == *list)
	{
		// r(list);
		temp = (*list)->next;
		*list = temp;
		return ;
	}
	temp->prev = (*list)->prev;
	(*list)->next = temp->next;
	(*list)->prev = temp;
	temp->next->prev = *list;
	temp->next = *list;
	*list = temp;
}

/*
	rra・rrb処理を実施します
*/
int rr(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return (0);
	temp = (*list)->prev;
	*list = temp;
	return (1);
}
int	reverse_rotate(t_data *data, int mode)
{
	if (mode == A)
	{
		ft_printf("rra\n");
		return (rr(&data->a));
	}
	else if (mode == B)
	{
		ft_printf("rrb\n");
		return (rr(&data->b));
	}
	else
	{
		ft_printf("rrr\n");
		rr(&data->a);
		rr(&data->b);
	}
	return (0);
}
