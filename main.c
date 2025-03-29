#include "push_swap.h"

void test(t_data *data)
{
	t_list *temp;

	printf("a: ");
	temp = data->a;
	if (data->a)
	{
		while ((data->a)->prev != temp)
		{
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("%d ", temp->val);
	}
	printf("/ b: ");
	if (data->b)
	{
		temp = data->b;
		while ((data->b)->prev != temp)
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
/*
	スタックの大きさを取得する
*/
ssize_t get_stack_size(t_list **list)
{
	t_list *temp;
	int ret;

	if (!*list)
		return (0);
	ret = 0;
	temp = *list;
	while(temp->next != *list)
	{
		ret++;
		temp = temp->next;
	}
	return ++ret;
}

/*
	3件以下のスタックを昇順にソートする
*/
void sort_under_three(t_list **list)
{
	if ((*list)->next == *list)
		return ;
	if((*list)->next->next == *list)
	{
		if ((*list)->val > (*list)->next->val)
			s(list);
		return ;
	}
	if ((*list)->next->next->next == *list)
	{
		if ((*list)->next->val > (*list)->val
		&& (*list)->next->val > (*list)->next->next->val)
			rr(list);
		if ((*list)->val > (*list)->next->val
		&& (*list)->val > (*list)->next->next->val)
			r(list);
		if ((*list)->val > (*list)->next->val)
			s(list);
		return ;
	}
}

/*
	基準値以上・以下のデータをBスタックに移動する
*/
ssize_t move_b_by_pivot(t_data *data, int mode, int pivot)
{
	ssize_t size;
	int		idx;
	ssize_t ret;

	idx = 0;
	ret = 0;
	size = get_stack_size(&data->a);
	while (idx < size)
	{
		if ((mode && data->a->val >= pivot) || (!mode && data->a->val < pivot))
		{
			push(data, B);
			ret++;
		}
		else
		{
			r(&data->a);
		}
		idx++;
	}
	return (ret);
}
ssize_t move_a_by_pivot(t_data *data, int mode, int pivot)
{
	ssize_t size;
	int		idx;
	ssize_t ret;

	idx = 0;
	ret = 0;
	size = get_stack_size(&data->b);
	while (idx < size)
	{
		if ((mode && data->b->val >= pivot) || (!mode && data->b->val < pivot))
		{
			push(data, A);
			ret++;
		}
		else
		{
			r(&data->b);
		}
		idx++;
	}
	return (ret);
}
/*
	Bスタックの内容をソートする
*/
void sort_b(t_data *data)
{
	ssize_t size;
	ssize_t save;
	int median;

	size = get_stack_size(&data->b);
	if (size < 3)
	{
		sort_under_three(&data->b);
		while(data->b)
		{
			push(data, A);
			r(&data->a);
		}
		return ;
	}
	median = find_median(&data->b, size);
	save = move_a_by_pivot(data, OVER, median);
	sort_b(data);
	while (save--)
		push(data, B);
	sort_b(data);
}
/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_data data;
	int		median;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	data.a = read_args(argc, argv);
	data.b = NULL;
	median = find_median(&data.a, argc - 1);
	move_b_by_pivot(&data, UNDER, median);
	sort_b(&data);
	move_b_by_pivot(&data, OVER, median);
	sort_b(&data);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
