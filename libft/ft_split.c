/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuyu <yuyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:17:24 by yuyu              #+#    #+#             */
/*   Updated: 2023/11/05 19:15:38 by yuyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

static void	free_all(char **ans, char index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(ans[i]);
		i++;
	}
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
				s = ft_substr(str + i - check, 0, check);
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

char	**ft_split(char const *s, char c)
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
		free(ans);
		return (0);
	}
	ans[count] = 0;
	free(str);
	return (ans);
}
