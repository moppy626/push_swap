/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:51:36 by mmachida          #+#    #+#             */
/*   Updated: 2025/04/15 23:23:44 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	挿入ソート
*/
void	insertion_sort(t_data *data)
{
	ssize_t	idx;
	ssize_t	moved;

	if (!data->b)
		return ;
	idx = 0;
	moved = 0;
	idx += push(data, A);
	moved++;
	while (data->b)
	{
		while (data->a != data->a->prev && idx != 0
			&& data->a->val < data->b->val)
			idx -= rotate(data, A);
		idx += push(data, A);
		moved++;
		while (data->b && moved > idx
			&& data->a->prev->val > data->b->val)
		{
			idx += reverse_rotate(data, A);
		}
	}
	while (idx)
		idx -= rotate(data, A);
}

/*
	基準値以上・以下のデータをBスタックに移動する
*/
ssize_t	move_by_pivot(t_data *data, int ou, int ab, int pivot)
{
	ssize_t	size;
	int		idx;
	ssize_t	ret;

	idx = 0;
	ret = 0;
	if (ab == A)
		size = data->b_size;
	else
		size = data->a_size;
	while (idx++ < size)
		if (ab == A && ((ou && data->b->val >= pivot)
			|| (!ou && data->b->val < pivot)))
			ret += push(data, A);
		else if (ab == B && ((ou && data->a->val >= pivot)
			|| (!ou && data->a->val < pivot)))
			ret += push(data, B);
		else
			if (ab == A)
				rotate(data, B);
			else
				rotate(data, A);
	return (ret);
}

/*
	Bスタックの内容をソートする
*/
void	sort_b(t_data *data)
{
	ssize_t	size;
	ssize_t	save;
	int		median;

	size = data->b_size;
	if (size <= 20)
	{
		insertion_sort(data);
		while (data->b)
		{
			push(data, A);
			rotate(data, A);
		}
		return ;
	}
	median = find_median(&data->b, size);
	save = move_by_pivot(data, OVER, A, median);
	sort_b(data);
	while (save--)
		push(data, B);
	sort_b(data);
}
/*
	3件以下のスタックを昇順にソートする
*/
void	sort_under_three(t_data *data, ssize_t size)
{
	if (size <= 1)
		return ;
	if (size == 2)
	{
		if (data->a->val > data->a->next->val)
			swap(&data->a, A);
		return ;
	}
	if (size == 3)
	{
		if (data->a->next->val > data->a->val
		&& data->a->next->val > data->a->next->next->val)
		reverse_rotate(data, A);
		if (data->a->val > data->a->next->val
		&& data->a->val > data->a->next->next->val)
			rotate(data, A);
		if (data->a->val > data->a->next->val)
		swap(&data->a, A);
		return ;
	}
}
/*
	メイン関数
*/
int	main(int argc, char **argv)
{
	t_data	data;
	int		median;
	ssize_t	save;
	ssize_t	size;

	if (argc <= 1)
		return (0);
	data.a = read_args(argc, argv);
	data.a_size = get_stack_size(&data.a);
	data.b = NULL;
	data.b_size = 0;
	if (is_sorted(&data.a, data.a_size))
		return (0);
	if (data.a_size >  3)
	{
		size = data.a_size;
		median = find_median(&data.a, size);
		save = move_by_pivot(&data, UNDER, B, median);
		sort_b(&data);
		while (size > save++)
			push(&data, B);
		sort_b(&data);
	}
	else
		sort_under_three(&data, data.a_size);
	free_list(&data.a);
	free_list(&data.b);
}
