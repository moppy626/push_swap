/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:59:00 by mmachida          #+#    #+#             */
/*   Updated: 2025/06/22 17:54:04 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	新しい双方向リストの構造体を作成する
*/
t_list	*new_val(int val, t_list **list, char	**splited)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		error("malloc error\n", list, NULL, splited);
	new->val = val;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

/*
	双方向リストの最後に値を追加する
*/
void	add_back(t_list **lst, t_list *new, char **splited)
{
	t_list	*temp;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			temp = temp->next;
			if (temp->val == new->val)
				error("Some arguments are duplicates\n", lst, NULL, splited);
		}
		temp->next = new;
		new->prev = temp;
	}
}

/*
	パラメタで指定された数字を読み込む
*/
t_list	*read_args(int argc, char **argv)
{
	int		i;
	t_list	*ret;
	t_list	*new;
	char	**splited;

	ret = NULL;
	if (argc == 2)
	{
		i = 0;
		splited = ft_split(argv[1], ' ');
		if (splited == NULL)
			error("Faild in ft_split\n", &ret, NULL, NULL);
		while (splited[i])
		{
			new = new_val(to_int(splited[i++], &ret, splited), &ret, splited);
			add_back(&ret, new, splited);
		}
		free_splited(splited);
	}
	else
	{
		i = 1;
		while (i < argc)
		{
			new = new_val(to_int(argv[i++], &ret, NULL), &ret, NULL);
			add_back(&ret, new, NULL);
		}
	}
	ret->prev = new;
	new->next = ret;
	return (ret);
}

/*
	データ保存用の構造体をセットする
*/
void	set_data(int argc, char **argv, t_data *data)
{
	data->a = read_args(argc, argv);
	data->a_size = get_stack_size(&data->a);
	data->b = NULL;
	data->b_size = 0;
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
