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
	(*list)->prev = temp;
	temp->next->prev = *list;
	temp->next = *list;
	temp->prev = NULL;
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
	temp->prev = NULL;
	*from = (*from)->next;
	if (*from)
		(*from)->prev = NULL;
	if (!to || !(*to))
	{
		*to = temp;
		temp->next = NULL;
	}
	else
	{
		(*to)->prev = temp;
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
	temp->prev = last;
	(*list)->prev = NULL;
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
	(*list)->prev = last;
	last->prev = NULL;
	last->next = *list;
	temp->next = NULL;
	*list = last;
	
}