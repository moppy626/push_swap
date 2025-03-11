#include "push_swap.h"

void test(t_list **a, t_list **b)
{
	t_list *temp;

	printf("a: ");
	temp = *a;
	if (*a)
	{
		while ((*a)->prev != temp)
		{
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("%d ", temp->val);
	}
	printf("/ b: ");
	if (*b)
	{
		temp = *b;
		while ((*b)->prev != temp)
		{
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("%d ", temp->val);
	}
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

int get_stack_size(t_list **list)
{
	t_list *temp;
	int ret;

	ret = 0;
	temp = *list;
	while(temp->prev != *list)
	{
		ret++;
		temp = temp->next;
	}
	return ++ret;
}
void push_a_to_b(t_list **a, t_list **b, t_status *stat)
{
	t_list	*pivot;
	t_list	*temp;
	size_t	len;
	size_t	i;

	len = get_stack_size(a);
	pivot = *a;
	p(a, b, stat, 'b'); // ピボットをBに移動

	i = 0;
	while (i++ < len - 1)
	{
		temp = *a;
		if (temp->val < pivot->val)
			p(a, b, stat, 'b'); // 小さいものはBの前方
		else
		{
			r(a, 'a'); // 大きいものは後方
			p(a, b, stat, 'b');
			r(b, 'b'); // Bを回転させ後方に配置
		}
	}

	// BをAに戻す
	while (*b)
	{
		if ((*b)->val < pivot->val)
			rr(b, 'b');
		p(b, a, stat, 'a');
	}
}

/*
	クイックソートする
*/
void	quick_sort(t_list **a, t_list **b, t_status *stat)
{
	if (get_stack_size(a) <= 1)
		return ;
	push_a_to_b(a, b, stat);
	quick_sort(a, b, stat);
	quick_sort(a, b, stat);
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
	quick_sort(&a, &b, &stat);
	// shift_to_stack(&a, &b, &stat);
	free_list(&a);
	free_list(&b);
}
