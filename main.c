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
	t_list *head;

	if (!list)
		return ;
	head = *list;
	*list = (*list)->next;
	while (head != *list)
	{
		printf("list->val:%d\n", (*list)->val);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	free(head);
}

/*
	コスト計算
*/
void	calculation_cost(t_list **a, t_list **b)
{
	ssize_t cost_a;
	ssize_t cost_b;
	t_list *temp;
	t_list *last;

	cost_a = 0;
	cost_b = 0;
	last = (*a);
	while (last->next)
		last = last->next;
	temp = (*b);
	while (temp)
	{
		if((*a)->val > temp->val)
			cost_a++;
		// if(last->val > temp->val)
		// 	cost_b++;
		temp = temp->next;
	}
	cost_b++;
	printf("cost_a:%ld\n",cost_a);
	printf("cost_b:%ld\n",cost_b);
	temp = (*b);
	// if (cost_a < cost_b)
		while((*a)->val > (*b)->val)
			r(b);
	// else
	// {
	// 	rr(a);
	// 	while((*a)->val > (*b)->val)
	// 		r(b);
	// }
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
