/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmachida <mmachida@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 08:42:45 by user42            #+#    #+#             */
/*   Updated: 2025/04/12 22:37:06 by mmachida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**getmem(char const *s, char c);
static size_t	copy(char *s, char c, char **ret, size_t idx);

char	**ft_split(char const *s, char c)
{
	char		**ret;
	size_t		start;
	size_t		len;
	size_t		idx;

	ret = getmem(s, c);
	if (!ret)
		return (NULL);
	start = 0;
	idx = 0;
	while (s[start] == c)
		start++;
	while (start < ft_strlen(s))
	{
		len = copy((char *)&s[start], c, ret, idx++);
		if (len < 0)
			return (NULL);
		start += len;
		if (c != '\0')
			while (s[start] == c)
				start++;
	}
	ret[idx] = NULL;
	return (ret);
}

char	**getmem(char const *s, char c)
{
	char		**ret;
	size_t		start;
	size_t		idx;

	start = 0;
	idx = 0;
	if (!s)
		return (NULL);
	while (s[start] == c)
		start++;
	while (start < ft_strlen(s))
	{
		while (s[start] != c && s[start] != '\0')
			start++;
		idx++;
		if (c != '\0')
			while (s[start] == c)
				start++;
	}
	ret = malloc(sizeof(char *) * (idx + 1));
	return (ret);
}

static size_t	copy(char *s, char c, char **ret, size_t idx)
{
	size_t		len;
	char		*m;

	len = 0;
	while (s[len] != c && s[len] != '\0')
		len++;
	m = malloc(sizeof(char) * (len + 1));
	if (!m)
		return (-1);
	ret[idx] = ft_memcpy(m, s, len);
	ret[idx][len] = '\0';
	return (len);
}
