#include "push_swap.h"

/*
	split関数の戻り値をfreeする
*/
void free_splited(char **splited)
{
	int i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

/*
	新しい双方向リストの構造体を作成する
*/
t_list	*new_val(int val)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->val = val;
	list->prev = NULL;
	list->next = NULL;
	return (list);
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
			if(temp->val == new->val)
				error("Some arguments are duplicates\n", lst, splited);
		}
		temp->next = new;
		new->prev = temp;
	}
}

/*
	パラメタで指定された数字を読み込む
*/
t_list *read_args(int argc, char **argv)
{
	ssize_t	i;
	ssize_t	j;
	t_list *ret;
	t_list *new;
	char **splited;

	i = 1;
	j = 0;
	ret = NULL;
	while (i < argc)
	{
		j = 0;
		splited = ft_split(argv[i], ' ');
		while (splited[j])
		{
			new = new_val(to_int(splited[j], &ret, splited));
			add_back(&ret, new, splited);
			j++;
		}
		i++;
	}
	free_splited(splited);
	ret->prev = new;
	new->next = ret;
	return (ret);
}

/*
	リストを初期化する
*/
void free_list(t_list **list)
{
	t_list *tmp;
	t_list *last;

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
