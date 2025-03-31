#include "push_swap.h"

void test(t_data *data)
{
	t_list *temp;

	printf("a(%ld): ", data->a_size);
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
	printf("/ b(%ld): ", data->b_size);
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
// ssize_t get_stack_size(t_list **list)
// {
// 	t_list *temp;
// 	int ret;

// 	if (!*list)
// 		return (0);
// 	ret = 0;
// 	temp = *list;
// 	while(temp->next != *list)
// 	{
// 		ret++;
// 		temp = temp->next;
// 	}
// 	return ++ret;
// }

/*
	3件以下のスタックを昇順にソートする
*/
void sort_under_three(t_list **list, ssize_t size, int mode)
{
	// printf("size=%ld\n",size);
	if (size <= 1)
		return ;
	if(size == 2)
	{
		// printf("(*list)->val=%d, (*list)->next->val=%d\n", (*list)->val, (*list)->next->val);
		if ((*list)->val > (*list)->next->val)
			swap(list, mode);
		return ;
	}
	if (size == 3)
	{
		if ((*list)->next->val > (*list)->val
		&& (*list)->next->val > (*list)->next->next->val)
		reverse_rotate(list, mode);
		if ((*list)->val > (*list)->next->val
		&& (*list)->val > (*list)->next->next->val)
			rotate(list, mode);
		if ((*list)->val > (*list)->next->val)
		swap(list, mode);
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
	size = data->a_size;
	while (idx < size)
	{
		if ((mode && data->a->val >= pivot) || (!mode && data->a->val < pivot))
		{
			push(data, B);
			ret++;
		}
		else
		{
			rotate(&data->a, A);
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
	size = data->b_size;
	while (idx < size)
	{
		if ((mode && data->b->val >= pivot) || (!mode && data->b->val < pivot))
		{
			push(data, A);
			ret++;
		}
		else
		{
			rotate(&data->b, B);
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

	test(data);
	size = data->b_size;
	if (size <= 3)
	{
		sort_under_three(&data->b, size, B);
		while(data->b)
		{
			push(data, A);
			rotate(&data->a, A);
		}
		return ;
	}
	median = find_median(&data->b, size);
	// printf("median=%d\n",median);
	save = move_a_by_pivot(data, OVER, median);
	sort_b(data);
	while (save--)
		push(data, B);
	// printf("median=%d\n",median);
	sort_b(data);
}
/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_data data;
	int		median;
	ssize_t	save;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	data.a = read_args(argc, argv);
	data.a_size = argc - 1;
	data.b = NULL;
	data.b_size = 0;
	test(&data);
	median = find_median(&data.a, argc - 1);
	// printf("median=%d\n",median);
	save = move_b_by_pivot(&data, UNDER, median);
	sort_b(&data);
	// printf("median=%d\n",median);
	while (argc - 1 > save++)
		push(&data, B);
	// move_b_by_pivot(&data, OVER, median);
	sort_b(&data);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
