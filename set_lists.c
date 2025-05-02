/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_lists.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 21:59:00 by mmachida          #+#    #+#             */
/*   Updated: 2025/05/02 15:29:44 by mmachida         ###   ########.fr       */
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
	{
		error("malloc error\n", list, NULL, splited);
	}	
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
	ssize_t	i;
	ssize_t	j;
	t_list	*ret;
	t_list	*new;
	char	**splited;

	i = 1;
	ret = NULL;
	while (i < argc)
	{
		j = 0;
		splited = ft_split(argv[i++], ' ');
		if (splited == NULL)
			error("Faild in ft_split\n", &ret, NULL, NULL);
		while (splited[j])
		{
			new = new_val(to_int(splited[j++], &ret, splited), &ret, splited);
			add_back(&ret, new, splited);
		}
		free_splited(splited);
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
