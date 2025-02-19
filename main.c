#include "push_swap.h"

void error(char *msg, int len)
{
	write(1, msg, len);
	exit(EXIT_SUCCESS);
}

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
		new = malloc(sizeof(t_list));
		new->val = ft_atoi(argv[cnt]);
		new->next = NULL;
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
}