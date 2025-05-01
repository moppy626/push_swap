/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:01:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/01 23:54:32 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	ra・rb処理を実施します
*/
int	r(t_list **list)
{
	t_list	*temp;

	if (!list || !*list || *list == (*list)->next)
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
	t_list	*first;
	t_list	*second;
	t_list	*third;

	if (*list == (*list)->next)
		return ;
	if (mode == A)
		ft_printf("sa\n");
	else
		ft_printf("sb\n");
	first = *list;
	second = first->next;
	third = second->next;
	first->next  = third;
	third->prev = first;
	second->prev = first->prev;
	first->prev->next = second;
	second->next = first;
	first->prev = second;
	*list = second;
}

/*
	rra・rrb処理を実施します
*/
int	rr(t_list **list)
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
