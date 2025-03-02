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

t_list	*get(t_list	*temp ,int mode)
{
	if (mode % 2 == 0)
		return temp->next;
	else
		return temp->prev;
}

/*
	コスト計算
	mode0⇒Aの先頭がチェック対象・B右回転
	mode1⇒Aの先頭がチェック対象・B左回転
	mode2⇒Aの最後がチェック対象・B右回転
	mode3⇒Aの最後がチェック対象・B左回転
*/
ssize_t	cost(t_list **a, t_list **b, t_status *stat, int mode)
{
	ssize_t cost;
	t_list	*temp;
	int		val;

	cost = 0;
	temp = *b;
	if (mode >= 2)
		val = (*a)->prev->val;
	else
		val = (*a)->val;

	if (val < stat->b_min || stat->b_max < val)
		while (temp->val != stat->b_max)
		{
			temp = get(temp, mode);
			cost++;
		}
	else
		while (!(temp->val < val && val < temp->prev->val))
		{
			temp = get(temp, mode);
			cost++;
		}
	// if (!(mode == 3 && cost > 1))
	// 	cost++;
	return (++cost);
}

/*
	対象の数字を移動する
*/
void	move(t_list **a, t_list **b, t_status *stat, int mode)
{
	// if (stat->tu == 'u' && stat->r == 2 && cost > 1)
	// 	rrr(a, b);
	if (mode >= 2)
		rr(a);
	if ((*a)->val < stat->b_min || stat->b_max < (*a)->val)
		while ((*b)->val != stat->b_max)
			if (mode % 2 == 0)
				r(b);
			else
				rr(b);
	else
		while (!((*b)->val < (*a)->val && (*a)->val < (*b)->prev->val))
			if (mode % 2 == 0)
				r(b);
			else
				rr(b);
	p(a, b, stat);
}
/*
	スタックAの先頭もしくは一番後ろで
	一番コストの低いものを調べて移動する
*/
void	calculate_cost(t_list **a, t_list **b, t_status *stat)
{
	ssize_t		costs[4];
	int			idx;
	int			min;

	costs[0] = cost(a, b, stat, 0);
	costs[1] = cost(a, b, stat, 1);
	costs[2] = cost(a, b, stat, 2);
	costs[3] = cost(a, b, stat, 3);
	idx = 0;
	min = 0;
	while (idx < 4)
	{
		if (costs[idx] < costs[min])
			min = idx;
		idx++;
	}
	// printf ("costs[0]:%ld,costs[1]:%ld,costs[2]:%ld,costs[3]:%ld\n",costs[0],costs[1],costs[2],costs[3]);
	move(a, b, stat, min);

}
/*
	スタックBに入っているデータをスタックAに戻す
*/
int shift_to_stack(t_list **a, t_list **b, t_status *stat)
{
	t_list	*temp;
	ssize_t	rcost;
	ssize_t rrcost;

	rcost = 0;
	temp = *b;
	while (temp->val != stat->b_max)
	{
		temp = temp->next;
		rcost++;
	}
	rrcost = 0;
	temp = *b;
	while (temp->val != stat->b_max)
	{
		temp = temp->prev;
		rrcost++;
	}
	while ((*b)->val != stat->b_max)
		if (rcost < rrcost)
			r(b);
		else
			rr(b);
	while (*b)
		p(b, a, stat);
}
/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_list *a;
	t_list *b;
	t_status stat;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	a = read_args(argc, argv);
	b = NULL;
	stat.b_max = 0;
	stat.b_min = 0;
	p(&a, &b, &stat);
	p(&a, &b, &stat);
	if (b->val < b->next->val)
		r(&b);
	while (a)
		calculate_cost(&a, &b, &stat);
	shift_to_stack(&a, &b, &stat);

	printf("a\n");
	free_list(&a);
	printf("b\n");
	free_list(&b);
}
