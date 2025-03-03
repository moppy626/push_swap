#include "push_swap.h"

void test(t_list **a, t_list **b)
{
	t_list *temp;

	temp = *a;
	printf("a: ");
	while ((*a)->prev != temp)
	{
		printf("%d ", temp->val);
		temp = temp->next;
	}
	printf("%d ", temp->val);
	temp = *b;
	printf("/ b: ");
	while ((*b)->prev != temp)
	{
		printf("%d ", temp->val);
		temp = temp->next;
	}
	printf("%d ", temp->val);
	printf("\n");
}
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
			r(b, 'b');
		else
			rr(b, 'b');
	while (*b)
		p(a, b, stat, 'a');
}

/*
	コスト計算
	mode0⇒Aの先頭がチェック対象・B上回転
	mode1⇒Aの先頭がチェック対象・B下回転
	mode2⇒Aの最後がチェック対象・B上回転
	mode3⇒Aの最後がチェック対象・B下回転
*/
ssize_t	cost(t_list **a, t_list **b, t_status *stat, int mode)
{

}

/*
	対象の数字を移動する
*/
void	move(t_list **a, t_list **b, t_status *stat, int mode)
{

	p(a, b, stat, 'b');
}
/*
	スタックAの先頭もしくは一番後ろで
	一番コストの低いものを調べて移動する
*/
void	calculate_cost(t_list **a, t_list **b, t_status *stat)
{

	move(a, b, stat, 0);
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
	stat.a_size = argc;
	stat.b_max = 0;
	stat.b_min = 0;
	p(&a, &b, &stat, 'b');
	p(&a, &b, &stat, 'b');
	test(&a, &b);
	if (b->val < b->next->val)
		r(&b, 'b');
	while (a)
		calculate_cost(&a, &b, &stat);
	shift_to_stack(&a, &b, &stat);
	free_list(&a);
	free_list(&b);
}
