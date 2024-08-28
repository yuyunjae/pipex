/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:17:24 by yuyu              #+#    #+#             */
/*   Updated: 2024/08/22 20:27:37 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_find_all(char *s, char c, int *length)
{
	int		i;
	int		count;
	char	before_c;

	*length = ft_strlen(s);
	i = -1;
	count = 0;
	before_c = 0;
	while (++i < *length)
	{
		if (s[i] == c)
			s[i] = 0;
		if (s[i] == 0 && before_c != 0)
			count++;
		before_c = s[i];
	}
	if (before_c != 0)
		count++;
	return (count);
}

void	free_all(char **ans, char index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ans[i]);
		i++;
	}
	free(ans);
}

static char	*ft_substr_add_s(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = ft_strlen(s);
	if (i <= start || len == 0)
	{
		str = ft_calloc(1, 1);
		return (str);
	}
	i = ft_strlen(s + start);
	if (len > i)
		len = i;
	str = ft_calloc(len + 2, 1);
	if (!str)
		return (0);
	ft_strlcpy(str, s + start, len + 1);
	str[len] = '/';
	str[len + 1] = 0;
	return (str);
}

static int	ft_split_all(char *str, char **ans, int length, int i)
{
	char	*s;
	int		check;
	int		index;

	check = 0;
	index = 0;
	while (++i <= length)
	{
		if (str[i] == 0)
		{
			if (check > 0)
			{
				s = ft_substr_add_s(str + i - check, 0, check);
				if (!s)
				{
					free_all(ans, index);
					return (0);
				}
				ans[index++] = s;
			}
			check = -1;
		}
		check++;
	}
	return (1);
}

char	**pipex_split(char const *s, char c)
{
	char	**ans;
	char	*str;
	int		count;
	int		length;

	str = ft_strdup(s);
	if (!str)
		return (0);
	count = ft_find_all(str, c, &length);
	ans = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ans)
	{
		free(str);
		return (0);
	}
	if (!ft_split_all(str, ans, length, -1))
	{
		free(str);
		return (0);
	}
	ans[count] = 0;
	free(str);
	return (ans);
}
