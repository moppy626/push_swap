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
	リストの中央値を取得
*/
void sort_median(int	ary[], ssize_t from, ssize_t to)
{
	ssize_t low;
	ssize_t high;
	int		temp;

	// printf("from=%ld, to=%ld\n", from, to);
	if(from >= to)
		return ;
	low = from;
	high = to;
	while (1)
	{
		while(ary[low] < ary[from])
			low++;
		while (ary[high] > ary[from])
			high--;
		if (low >= high)
			break ;
		temp = ary[high];
		ary[high] = ary[low];
		ary[low] = temp;
		low++;
		high--;
	}
	sort_median(ary, from, low - 1);
	sort_median(ary, high + 1, to);
}

/*
	リストの中央値を取得
*/
int find_median(t_list **list, ssize_t size)
{
	t_list *temp;
	ssize_t idx;
	int	ary[size];

	if (!*list)
		return (0);
	idx = 0;
	temp = *list;
	while(temp->next != *list)
	{
		ary[idx] = temp->val;
		temp = temp->next;
		idx++;
	}
	ary[idx] = temp->val;
	sort_median(ary, 0, size - 1);
	idx = 0;
	return (ary[size / 2]);
}

/*
	中央値以下のデータをBスタックに移動する
*/
void move_b_under_median(t_data *data)
{
	int		median;
	t_list	*top;
	ssize_t size;
	ssize_t	idx;

	size = get_stack_size(&data->a);

	median = find_median(&data->a, size);
	idx = 0;
	printf("median=%d\n", median);
	while (idx < size)
	{
		if (data->a->val < median)
			pb(data);
		else
			r(&data->a);
		idx++;
	}
}

/*
	メイン関数
*/
int main(int argc, char **argv)
{
	t_data data;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	data.a = read_args(argc, argv);
	data.a_size = argc;
	data.b = NULL;
	data.b_size = 0;
	move_b_under_median(&data);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
