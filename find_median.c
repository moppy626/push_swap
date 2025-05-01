/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_median.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 21:50:18 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/01 23:51:17 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	配列をソートする
*/
void	sort_median(int ary[], ssize_t from, ssize_t to)
{
	ssize_t	low;
	ssize_t	high;
	int		temp;

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
int	find_median(t_data *data, t_list **list, ssize_t size)
{
	t_list	*temp;
	ssize_t	idx;
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
