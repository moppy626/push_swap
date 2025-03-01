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
		printf("list->val:%d\n", (*list)->val);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	printf("list->val:%d\n", last->val);
	free(last);
}

/*
	コスト計算
*/
void	calculation_cost(t_list **a, t_list **b)
{
	ssize_t	cost_r;
	ssize_t	cost_l;
	t_list	*temp_r;
	t_list	*temp_l;

	cost_r = 0;
	temp_r = *b;
	while (!(temp_r->prev->val < (*a)->val && (*a)->val < temp_r->val))
	{
		printf("(*a)->val:%d\n", (*a)->val);
		printf("temp_r->prev->val:%d\n", temp_r->prev->val);
		printf("temp_r->val:%d\n",temp_r->val);
		temp_r = temp_r->next;
		cost_r++;
	}
	// cost_l = 0;
	// temp_l = *a;
	// while (!(temp_l->prev->val < (*b)->val && (*b)->val < temp_l->val))
	// {
	// 	temp_l = temp_l->prev;
	// 	cost_l++;
	// }
	// printf("cost_r:%ld, cost_l:%ld\n",cost_r,cost_l);
	// p(a, b);
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
	p(&a, &b);
	p(&a, &b);
	if (b->val > b->next->val)
		r(&b);
	// while (a)
		calculation_cost(&a, &b);

	// t_list *temp;
	// temp = a;
	// while(temp->next)
	// 	temp = temp->next;
	// while(temp)
	// {
	// 	printf("a->val=%d\n", temp->val);
	// 	temp = temp->prev;
	// }
	printf("a\n");
	free_list(&a);
	printf("b\n");
	free_list(&b);
}
