#include "push_swap.h"

void	r_src(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->next;
	*list = temp;
}

/*
	ra・rb処理を実施します
*/
void	r(t_list **list, char target)
{
	r_src(list);
	ft_printf("r%c\n", target);
}

/*
	sa・sb処理を実施します
*/
void	s(t_list **list, char target)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->next;
	if (temp->next == *list)
	{
		r_src(list);
		return ;
	}
	temp->prev = (*list)->prev;
	(*list)->next = temp->next;
	(*list)->prev = temp;
	temp->next->prev = *list;
	temp->next = *list;
	*list = temp;
	ft_printf("s%c\n", target);
}

void	rr_src(t_list **list)
{
	t_list	*temp;

	if (*list == (*list)->next)
		return ;
	temp = (*list)->prev;
	*list = temp;
}
/*
	rra・rrb・rrr処理を実施します
*/
void	rr(t_list **list, char target)
{
	rr_src(list);
	ft_printf("rr%c\n", target);
}

/*
	rrr処理を実施します
*/
void	rrr(t_list **a, t_list **b)
{
	rr_src(a);
	rr_src(b);
	ft_printf("rrr\n");
}