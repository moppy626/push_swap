#include "push_swap.h"

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
	pa・pb処理を実施します
*/
void	p(t_list **from, t_list **to)
{
	t_list	*temp;

	
	

}

/*
	ra・rb・rr処理を実施します
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
	rra・rrb・rrr処理を実施します
*/
void	rr(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->prev;
	*list = temp;
}