#include "push_swap.h"

/*
	sa・sb処理を実施します
*/
void	s(t_list **list)
{
	t_list	*temp;

	if (!(*list) || !(*list)->next)
		return ;
	temp = (*list)->next;
	(*list)->next = temp->next;
	temp->next = (*list);
	(*list) = temp;
}

/*
	pa・pb処理を実施します
*/
void	p(t_list **from, t_list **to)
{
	t_list	*temp;

	if (!from || !(*from))
		return ;
	temp = *from;
	*from = (*from)->next;
	if (!to || !(*to))
	{
		*to = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = *to;
		*to = temp;
	}
}

/*
	ra・rb・rr処理を実施します
*/
void	r(t_list **list)
{
	t_list	*temp;
	t_list	*last;


	if (!(*list) || !(*list)->next)
		return ;
	temp = *list;
	*list = (*list)->next;

	last = *list;
	while(last->next)
		last = last->next;
	last->next = temp;
	temp->next = NULL;
}

/*
	rra・rrb・rrr処理を実施します
*/
void	rr(t_list **list)
{
	t_list	*temp;
	t_list	*last;

	if (!(*list) || !(*list)->next)
		return ;
	last = *list;
	while(last->next)
		last = last->next;
	temp = *list;
	while(temp->next != last)
		temp = temp->next;
	last->next = *list;
	temp->next = NULL;
	*list = last;
	
}