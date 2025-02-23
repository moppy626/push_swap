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
		printf("argc[cnt]:%s\n", argv[cnt]);
		new = new_val(ft_atoi(argv[cnt]), tmp);
		if (!ret)
			ret = new;
		else
			tmp->next = new;
		tmp = new;
		cnt++;
	}
	return (ret);
}

/*
	リストを初期化する
*/
void free_list(t_list **list)
{
	t_list *tmp;

	if (!list)
		return ;
	while (*list)
	{
		printf("list->val:%d\n", (*list)->val);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}

/*
	コスト計算
*/
void	calculation_cost(t_list **a, t_list **b)
{
	ssize_t cost_a;
	ssize_t cost_b;
	t_list *temp;

	temp = (*b);
	while ((*a)->val > temp->val)
	{
		temp = temp->next;
		cost_a++;
	}

	



	p(a, b);
}

/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_list *a;
	t_list *b;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	a = read_args(argc, argv);
	b = NULL;
	// p(&a, &b);
	// p(&a, &b);
	// if (b->val > b->next->val)
	// 	r(&b);
	// while (a)
	// 	calculation_cost(&a, &b);
	printf("a\n");
	free_list(&a);
	printf("b\n");
	free_list(&b);
}
