#include "push_swap.h"

/*
	ra・rb処理を実施します
*/
int	rotate(t_list **list, int mode)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return (0);
	temp = (*list)->next;
	*list = temp;
	if (mode == A)
		ft_printf("ra\n");
	else
		ft_printf("rb\n");
	return (1);
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
int	reverse_rotate(t_list **list, int mode)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return (0);
	temp = (*list)->prev;
	*list = temp;
	if (mode == A)
		ft_printf("rra\n");
	else
		ft_printf("rrb\n");
	return (1);
}
