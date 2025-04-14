#include "push_swap.h"

void test(t_data *data)
{
	t_list *temp;

	if (data->a)
	{
		printf("a(%ld): ", data->a_size);
		temp = data->a;
		while ((data->a)->prev != temp)
		{
			printf("%d ", temp->val);
			temp = temp->next;
		}
		printf("%d ", temp->val);
	}
	if (data->b)
	{
		printf("/ b(%ld): ", data->b_size);
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
	挿入ソート
*/
void insertion_sort(t_data *data)
{
	ssize_t idx;
	ssize_t moved;

	if (!data->b)
		return ;
	idx = 0;
	moved = 0;
	idx += push(data, A);
	moved++;
	while (data->b)
	{
		while (data->a != data->a->prev && idx != 0 && data->a->val < data->b->val)
			idx -= rotate(data, A);
		idx += push(data, A);
		moved++;
		while (data->b && moved > idx && data->a->prev->val > data->b->val)
		{
			idx += reverse_rotate(data, A);
		}
	}
	while (idx)
		idx -= rotate(data, A);
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
				rotate(data, B);
			else
				rotate(data, A);
	return (ret);
}
/*
	ソート済みチェック
*/
int is_sorted(t_list **list, ssize_t size)
{
	ssize_t idx;
	t_list *temp;

	if (!*list)
		return (0);
	idx = 0;
	temp = *list;
	while (idx < size - 1)
	{
		if (temp->val > temp->next->val)
			return (0);
		temp = temp->next;
		idx++;
	}
	return (1);
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
	Bスタックの内容をソートする
*/
void sort_b(t_data *data)
{
	ssize_t size;
	ssize_t save;
	int median;

	size = data->b_size;
	if (size <= 20)
	{
		insertion_sort(data);
		while(data->b)
		{
			push(data, A);
			rotate(data, A);
		}
		return ;
	}
	median = find_median(&data->b, size);
	save = move_by_pivot(data, OVER, A, median);
	sort_b(data);
	while (save--)
		push(data, B);
	sort_b(data);
}
/*
	3件以下のスタックを昇順にソートする
*/
void sort_under_three(t_data *data, ssize_t size)
{
	if (size <= 1)
		return ;
	if(size == 2)
	{
		if (data->a->val > data->a->next->val)
			swap(&data->a, A);
		return ;
	}
	if (size == 3)
	{
		if (data->a->next->val > data->a->val
		&& data->a->next->val > data->a->next->next->val)
		reverse_rotate(data, A);
		if (data->a->val > data->a->next->val
		&& data->a->val > data->a->next->next->val)
			rotate(data, A);
		if (data->a->val > data->a->next->val)
		swap(&data->a, A);
		return ;
	}
}
/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_data data;
	int		median;
	ssize_t	save;
	ssize_t size;

	if (argc <= 1)
		return (0);
	data.a = read_args(argc, argv);
	data.a_size = get_stack_size(&data.a);
	data.b = NULL;
	data.b_size = 0;
	if (is_sorted(&data.a, data.a_size))
		return (0);
	if (data.a_size >  3)
	{
		size = data.a_size;
		median = find_median(&data.a, size);
		save = move_by_pivot(&data, UNDER, B, median);
		sort_b(&data);
		while (size > save++)
			push(&data, B);
		sort_b(&data);
	}
	else
		sort_under_three(&data, data.a_size);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
