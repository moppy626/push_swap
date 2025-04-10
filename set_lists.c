#include "push_swap.h"

/*
	エラーメッセージを出力して処理を終了する
*/
void error(char *msg, int len)
{
	write(1, msg, len);
	exit(EXIT_SUCCESS);
}

/*
	新しい構造体を作成する
*/
t_list *new_val(int val, t_list *prev)
{
	t_list *new;

	new = malloc(sizeof(t_list));
	new->prev = prev;
	new->val = val;
	new->next = NULL;

	return (new);
}

/*
	int型かどうかチェックする
*/
int is_int(char *str)
{
}

/*
	パラメタで指定された数字を読み込む
*/
t_list *read_args(int argc, char **argv)
{
	ssize_t	cnt;
	t_list *ret;
	t_list *tmp;
	t_list *new;

	cnt = 1;
	ret = NULL;
	tmp = ret;
	while (cnt < argc)
	{
		// printf("argc[cnt]:%s\n", argv[cnt]);
		new = new_val(ft_atoi(argv[cnt]), tmp);
		if (!ret)
			ret = new;
		else
			tmp->next = new;
		tmp = new;
		cnt++;
	}
	ret->prev = tmp;
	tmp->next = ret;
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
	*list = *list;
	while (last != *list)
	{
		// printf("list->val:%d\n", (*list)->val);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	// printf("list->val:%d\n", last->val);
	free(last);
}
