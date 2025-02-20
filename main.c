#include "push_swap.h"

void error(char *msg, int len)
{
	write(1, msg, len);
	exit(EXIT_SUCCESS);
}

/*
	新しい構造体を作成する
*/
t_list *new_val(int val)
{
	t_list *new;

	new = malloc(sizeof(t_list));
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
		// if(ft_isdigit(argv[cnt]))
		new = new_val(ft_atoi(argv[cnt]));
		if (!ret)
			ret = new;
		else
			tmp->next = new;
		tmp = new;
		cnt++;
	}
	return (ret);
}

void free_list(t_list **list)
{
	t_list *tmp;

	while (*list)
	{
		printf("list->val:%d\n", (*list)->val);
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
}



int main(int argc, char **argv)
{
	t_list *a;
	t_list *b;

	if (argc <= 1)
		error("Error\nAt least one more argument is required.\n", 46);
	a = read_args(argc, argv);
	printf("a->val:%d", a->val);
	printf("OK?\n");
	free_list(&a);
	free_list(&b);
}