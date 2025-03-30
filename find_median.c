#include "push_swap.h"


/*
	配列をソートする
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
	// printf("size=%ld\n", size);
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