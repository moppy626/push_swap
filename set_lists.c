#include "push_swap.h"

static int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

/*
	split関数の戻り値をfreeする
*/
void free_splited(char **splited)
{
	int i;

	i = 0;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}

/*
	エラーメッセージを出力して処理を終了する
*/
void error(char *msg, t_list **lst, char **splited)
{
	ft_printf(msg);
	if(splited)
		free_splited(splited);
	if (lst)
		free_list(lst);
	exit(EXIT_SUCCESS);
}

/*
	int型への変換を行う
*/
int	to_int(const char *str, t_list **lst, char **splited)
{
	long	ret;
	int		i;
	int		fugou;

	i = 0;
	while (is_space((char)str[i]))
		i++;
	fugou = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			fugou = -1;
	if (!('0' <= str[i] && str[i] <= '9'))
		error("Error\n Argument must be number\n", lst, splited);
	ret = 0;
	while (str[i] && str[i] != '.')
	{	
		printf("ret:%ld\n",ret);
		if (!('0' <= str[i] && str[i] <= '9'))
			error("Error\n Argument must be number\n", lst, splited);
		else if ((fugou < 0) && (ret > 0) && (ret > (INT_MAX - (str[i] - '0' - 1)) / 10))
				error("Error\n Numeric value must be in the range of int\n", lst, splited);
		else if ((fugou >= 0) && (ret > (INT_MAX - (str[i] - '0')) / 10))
				error("Error\n Numeric value must be in the range of int\n", lst, splited);
		ret = (ret * 10) + (str[i++] - '0');
	}
	return (fugou * ret);
}

/*
	新しい双方向リストの構造体を作成する
*/
t_list	*new_val(int val)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->val = val;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}
/*
	双方向リストの最後に値を追加する
*/
void	add_back(t_list **lst, t_list *new, char **splited)
{
	t_list	*temp;

	if (!lst || !(*lst))
	{
		*lst = new;
		return ;
	}
	else
	{
		temp = *lst;
		while (temp->next != NULL)
		{
			temp = temp->next;
			if(temp->val == new->val)
				error("Error\n Some arguments are duplicates\n", lst, splited);
		}
		temp->next = new;
		new->prev = temp;
	}
}

/*
	パラメタで指定された数字を読み込む
*/
t_list *read_args(int argc, char **argv)
{
	ssize_t	i;
	ssize_t	j;
	t_list *ret;
	t_list *new;
	char **splited;

	i = 1;
	j = 0;
	ret = NULL;
	while (i < argc)
	{
		j = 0;
		splited = ft_split(argv[i], ' ');
		while (splited[j])
		{
			new = new_val(to_int(splited[j], &ret, splited));
			add_back(&ret, new, splited);
			j++;
		}
		i++;
	}
	free_splited(splited);
	ret->prev = new;
	new->next = ret;
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
	// *list = *list;
	while (last != *list)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
	}
	free(last);
}
