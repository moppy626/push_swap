/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 23:56:15 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/14 23:41:44 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	エラーメッセージを出力して処理を終了する
*/
void	error(char *msg, t_list **lst1, t_list **lst2, char **splited)
{
	int	len;

	len = ft_strlen(msg);
	write(2, "Error\n", 6);
	write(2, msg, len);
	if (lst1)
		free_list(lst1);
	if (lst2)
		free_list(lst2);
	if (splited)
		free_splited(splited);
	exit (EXIT_FAILURE);
}

/*
	基準値以上・以下のデータをBスタックに移動する
*/
int	move_by_pivot(t_data *data, int ou, int ab, int pivot)
{
	int	size;
	int	idx;
	int	ret;

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

/*
	リスト内での最小値のインデックスを取得する
*/
int	get_min_idx(t_list *list, int size)
{
	t_list	*temp;
	int		min;
	int		min_idx;
	int		idx;

	if (!list)
		return (0);
	min = INT_MAX;
	idx = 0;
	temp = list;
	while (idx < size)
	{
		if (temp->val < min)
		{
			min = temp->val;
			min_idx = idx;
		}
		temp = temp->next;
		idx++;
	}
	if (min_idx > size / 2)
		return (min_idx - size);
	else
		return (min_idx);
}
