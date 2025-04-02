#include "push_swap.h"

/*
	pa・pb処理を実施します
*/
void	p(t_list **from, t_list **to)
{
	t_list	*temp;

	temp = *from;
	if (*from == (*from)->next)
		*from = NULL;
	else
	{
		(*from)->next->prev = (*from)->prev;
		(*from)->prev->next = (*from)->next;
		*from = (*from)->next;
	}
	if (!*to)
	{
		temp->prev = temp;
		temp->next = temp; 
	}
	else
	{
		temp->prev = (*to)->prev;
		temp->next = *to;
		(*to)->prev->next = temp;
		(*to)->prev = temp;
	}
	*to = temp;
}
int	push(t_data *data, int mode)
{
	if (mode == A)
	{
		p(&data->b, &data->a);
		data->a_size++;
		data->b_size--;
		ft_printf("pa\n");
	}
	else
	{
		p(&data->a, &data->b);
		data->b_size++;
		data->a_size--;
		ft_printf("pb\n");
	}
	return (1);
}




