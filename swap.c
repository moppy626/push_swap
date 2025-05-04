/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:01:54 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/03 18:40:29 by mmachida         ###   ########.fr       */
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
		write(1, "ra\n", 3);
		return (r(&data->a));
	}
	else if (mode == B)
	{
		write(1, "rb\n", 3);
		return (r(&data->b));
	}
	else
	{
		write(1, "rr\n", 3);
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
		write(1, "sa\n", 3);
	else
		write(1, "sb\n", 3);
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
		write(1, "rra\n", 4);
		return (rr(&data->a));
	}
	else if (mode == B)
	{
		write(1, "rrb\n", 4);
		return (rr(&data->b));
	}
	else
	{
		write(1, "rrr\n", 4);
		rr(&data->a);
		rr(&data->b);
	}
	return (0);
}
