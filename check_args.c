/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:56:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/03 17:40:48 by mmachida         ###   ########.fr       */
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
int	is_sorted(t_list **list, ssize_t size)
{
	ssize_t	idx;
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
	スタックの大きさを取得する
*/
ssize_t	get_stack_size(t_list **list)
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
