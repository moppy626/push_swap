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
ssize_t move_by_pivot(t_data *data, int ou, int ab, int pivot)
{
	ssize_t size;
	int		idx;
	ssize_t ret;

	idx = 0;
	ret = 0;
	if (ab == A)
		size = data->b_size;
	else
		size = data->a_size;
	while (idx++ < size)
		if (ab == A && ((ou && data->b->val >= pivot) || (!ou && data->b->val < pivot)))
			ret += push(data, A);
		else if (ab == B && ((ou && data->a->val >= pivot) || (!ou && data->a->val < pivot)))
			ret += push(data, B);
		else
			if (ab == A)
				rotate(&data->b, B);
			else
				rotate(&data->a, A);
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
	save = move_by_pivot(data, OVER, A, median);
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
	save = move_by_pivot(&data, UNDER, B, median);
	sort_b(&data);
	// printf("median=%d\n",median);
	while (argc - 1 > save++)
		push(&data, B);
	sort_b(&data);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
