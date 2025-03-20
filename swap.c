#include "push_swap.h"

/*
	ra・rb処理を実施します
*/
void	r(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->next;
	*list = temp;
}

/*
	sa・sb処理を実施します
*/
void	s(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->next;
	if (temp->next == *list)
	{
		r(list);
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
	rra・aab処理を実施します
*/
void	rr(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->prev;
	*list = temp;
}

/*
	rrr処理を実施します
*/
void	rrr(t_list **a, t_list **b)
{
	rr(a);
	rr(b);
}