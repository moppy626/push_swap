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
	基準値以上・以下のデータを指定のスタックに移動する
*/
void move_by_pivot(t_list **from, t_list **to, int mode, int pivot)
{
	ssize_t size;
	int		idx;

	idx = 0;
	size = get_stack_size(from);
	while (idx < size)
	{
		if (mode && (*from)->val >= pivot)
			p(from, to);
		else if (!mode && (*from)->val < pivot)
			p(from, to);
		else
			r(from);
		idx++;
	}
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
	メイン関数
*/
int main(int argc, char **argv)
{
	t_data data;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	data.a = read_args(argc, argv);
	data.a_size = argc - 1;
	data.b = NULL;
	data.b_size = 0;
	int median = find_median(&data.a, data.a_size);
	printf("median=%d\n", median);
	move_by_pivot(&data.a, &data.b, 1, median);
	test(&data);
	free_list(&data.a);
	free_list(&data.b);
}
