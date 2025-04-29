/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:56:55 by mmachida          #+#    #+#             */
/*   Updated: 2025/04/15 22:56:55 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	Outputs an error message and terminates the process
*/
void	error(char *msg, t_list **lst1, t_list **lst2, char **splited)
{
	ft_printf("Error\n %s", msg);
	if (lst1)
		free_list(lst1);
	if (lst2)
		free_list(lst2);
	if (splited)
		free_splited(splited);
	exit (EXIT_FAILURE);
}

/*
	Judging blanks
*/
int	is_space(char c)
{
	if ((9 <= c && c <= 13) || c == 32)
		return (1);
	else
		return (0);
}

/*
	Convert to int type
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
		error("Argument must be number\n", lst, NULL, splited);
	ret = 0;
	while (str[i] && str[i] != '.')
	{	
		if (!('0' <= str[i] && str[i] <= '9'))
			error("Argument must be number\n", lst, NULL, splited);
		else if ((fugou < 0) && (fugou * ret < (INT_MIN + (str[i] - '0')) / 10))
			error("Out of int range\n", lst, NULL, splited);
		else if ((fugou >= 0) && (ret > (INT_MAX - (str[i] - '0')) / 10))
			error("Out of int range\n", lst, NULL, splited);
		ret = (ret * 10) + (str[i++] - '0');
	}
	return (fugou * ret);
}

/*
	Sorted Checks
*/
int	is_sorted(t_list **list, ssize_t size)
{
	ssize_t	idx;
	t_list	*temp;

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
	Get stack size
*/
ssize_t	get_stack_size(t_list **list)
{
	t_list	*temp;
	int		ret;

	if (!*list)
		return (0);
	ret = 0;
	temp = *list;
	while (temp->next != *list)
	{
		ret++;
		temp = temp->next;
	}
	return (++ret);
}
