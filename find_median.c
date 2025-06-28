/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:50:18 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/28 14:52:01 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	配列をソートする
*/
void	sort_median(int ary[], int from, int to)
{
	int	low;
	int	high;
	int	temp;

	if (from >= to)
		return ;
	low = from;
	high = to;
	while (1)
	{
		while (ary[low] < ary[from])
			low++;
		while (ary[high] > ary[from])
			high--;
		if (low >= high)
			break ;
		temp = ary[high];
		ary[high] = ary[low];
		ary[low] = temp;
		low++;
		high--;
	}
	sort_median(ary, from, low - 1);
	sort_median(ary, high + 1, to);
}

/*
	リストの中央値を取得
*/
int	find_median(t_data *data, t_list **list, int size)
{
	t_list	*temp;
	int		idx;
	int		*ary;

	if (!*list || size <= 0)
		return (0);
	ary = (int *)malloc(sizeof(int) * size);
	if (!ary)
		error("malloc error\n", &data->a, &data->b, NULL);
	idx = 0;
	temp = *list;
	while (temp->next != *list)
	{
		ary[idx] = temp->val;
		temp = temp->next;
		idx++;
	}
	ary[idx] = temp->val;
	sort_median(ary, 0, size - 1);
	idx = ary[size / 2];
	free(ary);
	return (idx);
}

/*
	スタックの大きさを取得する
*/
int	get_stack_size(t_list **list)
{
	t_list	*temp;
	int		ret;

	if (!*list)
		return (0);
	ret = 0;
	temp = *list;
	while (temp->next != *list)
	{
		ret++;
		temp = temp->next;
	}
	return (++ret);
}
