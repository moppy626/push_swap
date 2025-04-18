/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:56:15 by mmachida          #+#    #+#             */
/*   Updated: 2025/04/17 23:56:15 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
	{
		if (ab == A
			&& ((ou && data->b->val >= pivot) || (!ou && data->b->val < pivot)))
			ret += push(data, A);
		else if (ab == B
			&& ((ou && data->a->val >= pivot) || (!ou && data->a->val < pivot)))
			ret += push(data, B);
		else if (ab == A)
			rotate(data, B);
		else
			rotate(data, A);
	}
	return (ret);
}

/*
	split関数の戻り値をfreeする
*/
void	free_splited(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

/*
	リストを初期化する
*/
void	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*last;

	if (!list || !*list)
		return ;
	last = (*list)->prev;
	while (last != *list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	free(last);
}
