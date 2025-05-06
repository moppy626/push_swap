/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:56:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/06 11:35:46 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	空白を判定する
*/
int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

/*
	int型への変換を行う
*/
int	to_int(const char *str, t_list **lst, char **splited)
{
	long	ret;
	int		i;
	int		sign;

	i = 0;
	while (is_space((char)str[i]))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	ret = 0;
	if (!('0' <= str[i] && str[i] <= '9'))
		error("Argument must be Integer\n", lst, NULL, splited);
	while (str[i])
	{	
		if (!('0' <= str[i] && str[i] <= '9'))
			error("Argument must be Integer\n", lst, NULL, splited);
		else if ((sign < 0) && (sign * ret < (INT_MIN + (str[i] - '0')) / 10))
			error("Out of int range\n", lst, NULL, splited);
		else if ((sign >= 0) && (ret > (INT_MAX - (str[i] - '0')) / 10))
			error("Out of int range\n", lst, NULL, splited);
		ret = (ret * 10) + (str[i++] - '0');
	}
	return (sign * ret);
}

/*
	ソート済みチェック
*/
int	is_sorted(t_list **list, int size)
{
	int	idx;
	t_list	*temp;

	if (!*list)
		return (0);
	idx = 0;
	temp = *list;
	while (idx < size - 1)
	{
		if (temp->val > temp->next->val)
			return (0);
		temp = temp->next;
		idx++;
	}
	return (1);
}

/*
	リストから指定した箇所のポインタを取得する
*/
t_list	*get_idx(t_list **list, int get_idx)
{
	t_list	*temp;
	int	idx;

	idx = 0;
	temp = *list;
	while (get_idx != idx)
	{
		if (get_idx < 0)
		{
			temp = temp->prev;
			idx--;
		}
		else
		{
			temp = temp->next;
			idx++;
		}
	}
	return (temp);
}

/*
	ソート済みで先頭が最小でない場合、
	先頭を最小に合わせる
*/
int	rotate_sorted(t_data *data)
{
	int		min_idx;
	t_list	*temp;

	min_idx = get_min_idx(data->a, data->a_size);
	temp = get_idx(&data->a, min_idx);
	if (!is_sorted(&temp, data->a_size))
		return (0);
	while (min_idx != 0)
	{
		if (min_idx < 0)
		{
			reverse_rotate(data, A);
			min_idx++;
		}
		else
		{
			rotate(data, A);
			min_idx--;
		}
	}
	return (1);
}
